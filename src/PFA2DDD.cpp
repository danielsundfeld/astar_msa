/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Do a multiple sequence alignment reducing the search space
 * with pfa2ddd algorithm
 */
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

#include "AStar.h"
#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "PriorityList.h"
#include "Sequences.h"

using namespace std;

#define THREADS_NUM 4

PriorityList OpenList[THREADS_NUM];
ListType ClosedList[THREADS_NUM];

std::mutex queue_mutex[THREADS_NUM];
std::vector<Node> queue_nodes[THREADS_NUM];

std::atomic<bool> end_cond;

std::mutex final_node_mutex;
Node final_node(0);
std::atomic<int> final_node_count;

std::mutex sync_mutex;
std::atomic<int> sync_count;
std::condition_variable sync_condition;

/*!
 * Add a vector of nodes \a nodes to the PriorityList \a OpenList. Use the
 * \a ClosedList information to ignore expanded nodes.
 * This function is a expensive function and should be called with no locks.
 * Parallel access should never occur on \a OpenList and \a ClosedList
 */
void pfa2ddd_enqueue(std::vector<Node> &nodes, PriorityList &OpenList, ListType &ClosedList)
{
    open_list_iterator o_search;
    closed_list_iterator c_search;

    for (vector<Node>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
    {
        if ((o_search = OpenList.find(it->pos)) != OpenList.end())
        {
            // if score on open list is better, ignore this neighboor
            if (it->get_g() > open_list_return_g(o_search))
                continue;
        }
        if ((c_search = ClosedList.find(it->pos)) != ClosedList.end())
        {
            if (it->get_g() >= closed_list_return_g(c_search))
                continue;
            ClosedList.erase(it->pos);
        }
        //cout << Adding:\t" << *it << endl;
        OpenList.enqueue(*it);
    }
    return;
}

/*!
 * Process \a n as an possible answer. Check end phase 1
 */
void pfa2ddd_process_final_node(int tid, const Node &n)
{
    std::unique_lock<std::mutex> final_node_lock(final_node_mutex);

    // Better possible answer already found, discard n
    if (final_node.get_f() < n.get_f())
        return;

    if (n.pos.get_id(THREADS_NUM) == tid)
    {
        //cout << "[" << tid << "] Possible answer found: " << n << endl;
        // Broadcast the node
        final_node = n;
        final_node_count = 1;
        final_node_lock.unlock();

        for (int i = 0; i < THREADS_NUM; i++)
        {
            if (i != tid)
            {
                std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
                queue_nodes[i].push_back(n);
            }
        }
        return;
    }
    //cout << "[" << tid << "] Agreed with possible answer! " << n << "/" << final_node << endl;
    //if (n != final_node) cout << "BUG HERE!\n";
    final_node_lock.unlock();

    // Process a broadcast node
    if (++final_node_count == THREADS_NUM)
    {
        // This node have the highest priority between all Openlist.
        end_cond = true;
        return;
    }
    return;
}

//! Consume the queue with id \a tid
void pfa2ddd_consume_queue(int tid)
{
    std::unique_lock<std::mutex> queue_lock(queue_mutex[tid]);
    std::vector<Node> nodes_to_expand(queue_nodes[tid]);
    queue_nodes[tid].clear();
    queue_lock.unlock();

    pfa2ddd_enqueue(nodes_to_expand, OpenList[tid], ClosedList[tid]);
    return;
}

//! Sync all threads
void pfa2ddd_sync_threads()
{
    std::unique_lock<std::mutex> sync_lock(sync_mutex);
    if (++sync_count < THREADS_NUM)
        sync_condition.wait(sync_lock);
    else
    {
        sync_condition.notify_all();
        sync_count = 0;
    }
}

//! Execute the pfa2ddd algorithm until all nodes expand the same final node
void pfa2ddd_worker_inner(int tid, bool(*is_final)(const Coord &c))
{
    Node current;

    // Loop ended by pfa2ddd_process_final_node
    while (end_cond == false)
    {
        open_list_iterator o_search;
        closed_list_iterator c_search;

        // Start phase
        // Reduce the queue
        pfa2ddd_consume_queue(tid);

        // Dequeue phase
        if (OpenList[tid].dequeue(current) == false)
            continue;

        // Check if better node is already found
        if ((o_search = OpenList[tid].find(current.pos)) != OpenList[tid].end())
        {
            if (current.get_g() > open_list_return_g(o_search))
                continue;
        }
        // Or already opened
        if ((c_search = ClosedList[tid].find(current.pos)) != ClosedList[tid].end())
        {
            if (current.get_g() >= closed_list_return_g(c_search))
                continue;
        }

        //cout << "[" << tid << "] Opening node:\t" << current << endl;
        ClosedList[tid][current.pos] = current;

        if (is_final(current.pos))
        {
            pfa2ddd_process_final_node(tid, current);
            continue;
        }
        OpenList[tid].verifyMemory();

        // Expand phase
        vector<Node> neigh[THREADS_NUM] = {} ;
        current.getNeigh(neigh, THREADS_NUM);

        // Reconciliation phase
        for (int i = 0; i < THREADS_NUM; i++)
        {
            if (i == tid)
                pfa2ddd_enqueue(neigh[i], OpenList[i], ClosedList[i]);
            else
            {
                std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
                queue_nodes[i].insert(queue_nodes[i].end(), neigh[i].begin(), neigh[i].end());
            }
        }
    }
    return;
}

/*! 
 * Check end phase 2.
 * After everyone agreed that a possible answer is found, we must syncronize
 * the threads, consume the queue and check again, if the answer have the
 * lowest priority between all OpenLists
 * The queue consume and/or thread scheduling might have caused the final_node
 * to not have the lowest priority.
 */
bool pfa2ddd_check_stop(int tid)
{
    pfa2ddd_sync_threads();
    Node n = final_node;
    pfa2ddd_consume_queue(tid);
    if (OpenList[tid].get_highest_priority() < final_node.get_f())
    {
        //cout << "[" << tid << "] reporting early end!\n";
        end_cond = false;
    }
    pfa2ddd_sync_threads();
    if (end_cond == false)
    {
        ClosedList[tid].erase(n.pos);
        if (n.pos.get_id(THREADS_NUM) == tid)
            OpenList[tid].conditional_enqueue(n);
        return true;
    }
    return false;
}

//! Execute a pfa2ddd_worker thread. This thread have id \a tid
int pfa2ddd_worker(int tid, const Node &node_zero, bool(*is_final)(const Coord &c))
{
    if (tid == 0)
        OpenList[tid].enqueue(node_zero);

    // worker_inner is the main inner loop
    // check_stop syncs and check if is the optimal answer
    do {
        pfa2ddd_worker_inner(tid, is_final);
    } while (pfa2ddd_check_stop(tid));

    return 0;
}

/*!
 * Same a_star() function usage.
 * Starting function to do a pfa2ddd search.
 */
int pfa2ddd(const Node &node_zero, bool(*is_final)(const Coord &c))
{
    std::vector<std::thread> threads;

    // Initialize variables
    end_cond = false;
    sync_count = 0;

    // Create threads
    for (int i = 0; i < THREADS_NUM; ++i)
        threads.push_back(std::thread(pfa2ddd_worker, i, node_zero, is_final));

    // Wait for the end of all threads
    for (auto& th : threads)
        th.join();

    // Print answer
    cout << "Final score:\t" << final_node << endl;
    backtrace(ClosedList, THREADS_NUM);
    return 0;
}

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
std::atomic<int> priorities[THREADS_NUM];

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

//! Check if the answer is found
bool pfa2ddd_check_end(int tid, const Node &final_node, const Node &last_opened_node)
{

    // Check if my found node is the answer
    if (final_node.get_f() < last_opened_node.get_f())
    {
        int i;
        for (i = 0; i < THREADS_NUM; i++)
        {
            if (final_node.get_f() > priorities[i])
                break;
        }
        if (i == THREADS_NUM)
        {
            cout << "[" << tid << "] Final score:\t" << final_node << endl;
            end_cond = true;
            return true;
        }
    }
    return false;
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

//! Execute a pfa2ddd_worker thread. This thread have id \a tid
int pfa2ddd_worker(int tid, const Node &node_zero, bool(*is_final)(const Coord &c))
{
    Node current(0);
    Node final_node(0);

    if (tid == 0)
        OpenList[tid].enqueue(node_zero);

    while (end_cond == false)
    {
        open_list_iterator o_search;
        closed_list_iterator c_search;

        // Start phase
        // Check end condition
        if (pfa2ddd_check_end(tid, final_node, current))
            continue;
        // Reduce the queue
        pfa2ddd_consume_queue(tid);

        // Dequeue phase
        if (OpenList[tid].dequeue(current) == false)
            continue;
        priorities[tid] = current.get_f();

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
            if (current.get_f() < final_node.get_f())
                final_node = current;
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
    for (int i = 0; i < THREADS_NUM; ++i)
        priorities[i] = std::numeric_limits<int>::max();

    // Create threads
    for (int i = 0; i < THREADS_NUM; ++i)
        threads.push_back(std::thread(pfa2ddd_worker, i, node_zero, is_final));

    // Wait for the end of all threads
    for (auto& th : threads)
        th.join();

    // Print answer
    backtrace(ClosedList, THREADS_NUM);
    return 0;
}

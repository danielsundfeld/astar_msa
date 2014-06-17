/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <sched.h>
#include <thread>
#include <vector>

#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "PAStar.h"

using namespace std;

PAStar::PAStar(const Node &node_zero)
: nodes_count { },
  nodes_reopen { },
  final_node(0)
{
    end_cond = false;
    sync_count = 0;

    // Enqueue first node
    OpenList[0].enqueue(node_zero);
}

int PAStar::set_affinity(int tid)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1 << tid, &mask);
    return sched_setaffinity(0, sizeof(mask), &mask);
}

/*!
 * Add a vector of nodes \a nodes to the OpenList with id \a tid. Use the
 * ClosedList information to ignore expanded nodes.
 * This function is a expensive function and should be called with no locks.
 * Parallel access should never occur on OpenList and ClosedList with
 * same tids.
 */
void PAStar::enqueue(int tid, std::vector<Node> &nodes)
{
    closed_list_iterator c_search;

    for (vector<Node>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
    {
        if ((c_search = ClosedList[tid].find(it->pos)) != ClosedList[tid].end())
        {
            if (it->get_g() >= closed_list_return_g(c_search))
                continue;
            ClosedList[tid].erase(it->pos);
            nodes_reopen[tid] += 1;
        }
        //cout << Adding:\t" << *it << endl;
        OpenList[tid].conditional_enqueue(*it);
    }
    return;
}

//! Consume the queue with id \a tid
void PAStar::consume_queue(int tid)
{
    std::unique_lock<std::mutex> queue_lock(queue_mutex[tid]);
    std::vector<Node> nodes_to_expand(queue_nodes[tid]);
    queue_nodes[tid].clear();
    queue_lock.unlock();

    enqueue(tid, nodes_to_expand);
    return;
}

//! Wait something on the queue
void PAStar::wait_queue(int tid)
{
    std::unique_lock<std::mutex> queue_lock(queue_mutex[tid]);
    if (queue_nodes[tid].size() != 0)
        return;

    queue_condition[tid].wait(queue_lock);
    return;
}

//! Wake up everyone waiting on the queue
void PAStar::wake_all_queue()
{
    for (int i = 0; i < THREADS_NUM; ++i)
    {
        std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
        queue_condition[i].notify_one();
    }
    return;
}

//! Sync all threads
void PAStar::sync_threads()
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

//! Execute the pa_star algorithm until all nodes expand the same final node
void PAStar::worker_inner(int tid, bool(*is_final)(const Coord &c))
{
    Node current;

    // Loop ended by process_final_node
    while (end_cond == false)
    {
        closed_list_iterator c_search;

        // Start phase
        // Reduce the queue
        consume_queue(tid);

        // Dequeue phase
        if (OpenList[tid].dequeue(current) == false)
        {
            wait_queue(tid);
            continue;
        }
        nodes_count[tid] += 1;

        // Check if better node is already found
        if ((c_search = ClosedList[tid].find(current.pos)) != ClosedList[tid].end())
        {
            if (current.get_g() >= closed_list_return_g(c_search))
                continue;
            nodes_reopen[tid] += 1;
        }

        //cout << "[" << tid << "] Opening node:\t" << current << endl;
        ClosedList[tid][current.pos] = current;

        if (is_final(current.pos))
        {
            process_final_node(tid, current);
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
                enqueue(tid, neigh[i]);
            else if (neigh[i].size() != 0)
            {
                std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
                queue_nodes[i].insert(queue_nodes[i].end(), neigh[i].begin(), neigh[i].end());
                queue_condition[i].notify_one();
            }
        }
    }
    return;
}

/*!
 * Process \a n as an possible answer. Check end phase 1.
 * When a final node is first opened, it is broadcasted in all OpenLists.
 * When all OpenList open this node, it have the lowest priority among all
 * openlists, then it must proceed to Check end phase 2.
 * This is functions does not require synchronization between the threads.
 */
void PAStar::process_final_node(int tid, const Node &n)
{
    std::unique_lock<std::mutex> final_node_lock(final_node_mutex);

    // Better possible answer already found, discard n
    if (final_node.get_f() < n.get_f())
        return;

    if (n.pos.get_id(THREADS_NUM) == (unsigned int)tid)
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
                queue_condition[i].notify_one();
            }
        }
        // Process a broadcast node
        if (final_node_count == THREADS_NUM)
        {
            // This node have the highest priority between all Openlist.
            end_cond = true;
            return;
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

/*! 
 * Check end phase 2.
 * After everyone agreed that a possible answer is found, we must syncronize
 * the threads, consume the queue and check again, if the answer have the
 * lowest priority between all OpenLists
 * The queue consume and/or thread scheduling might have caused the final_node
 * to not have the lowest priority.
 * This is a very costly function, threads syncronization are called twice.
 */
bool PAStar::check_stop(int tid)
{
    wake_all_queue();
    sync_threads();
    Node n = final_node;
    consume_queue(tid);
    if (OpenList[tid].get_highest_priority() < final_node.get_f())
    {
        //cout << "[" << tid << "] reporting early end!\n";
        end_cond = false;
    }
    sync_threads();
    if (end_cond == false)
    {
        ClosedList[tid].erase(n.pos);
        if (n.pos.get_id(THREADS_NUM) == (unsigned int) tid)
            OpenList[tid].conditional_enqueue(n);
        return true;
    }
    return false;
}

//! Execute a worker thread. This thread have id \a tid
int PAStar::worker(int tid, bool(*is_final)(const Coord &c))
{
    set_affinity(tid);
    // worker_inner is the main inner loop
    // check_stop syncs and check if is the optimal answer
    do {
        worker_inner(tid, is_final);
    } while (check_stop(tid));

    return 0;
}

void PAStar::print_nodes_count()
{
    long long int nodes_total = 0;
    long long int open_list_total = 0;
    long long int closed_list_total = 0;
    long long int nodes_reopen_total = 0;

    cout << "Total nodes count:" << endl;
    for (int i = 0; i < THREADS_NUM; ++i)
    {
        cout << "tid " << i
             << "\tOpenList:" << OpenList[i].size()
             << "\tClosedList:" << ClosedList[i].size()
             << "\tReopen:" << nodes_reopen[i]
             << "\tTotal: " << nodes_count[i] << endl;
        open_list_total += OpenList[i].size();
        closed_list_total += ClosedList[i].size();
        nodes_reopen_total += nodes_reopen[i];
        nodes_total += nodes_count[i];
    }
    cout << "Sum"
          << "\tOpenList:" << open_list_total
          << "\tClosedList:" << closed_list_total
          << "\tReopen:" << nodes_reopen_total
          << "\tTotal: " << nodes_total << endl;
}

void PAStar::print_answer()
{
    cout << "Final score:\t" << final_node << endl;
    backtrace(ClosedList, THREADS_NUM);
    print_nodes_count();
}

/*!
 * Same a_star() function usage.
 * Starting function to do a pa_star search.
 */
int PAStar::pa_star(const Node &node_zero, bool(*is_final)(const Coord &c))
{
    PAStar pastar_instance(node_zero);
    std::vector<std::thread> threads;

    // Create threads
    for (int i = 0; i < THREADS_NUM; ++i)
        threads.push_back(std::thread(&PAStar::worker, &pastar_instance, i, is_final));

    // Wait for the end of all threads
    for (auto& th : threads)
        th.join();

    pastar_instance.print_answer();
    return 0;
}

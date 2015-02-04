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
#include "TimeCounter.h"

template < int N >
PAStar<N>::PAStar(const Node<N> &node_zero, const struct PAStarOpt &opt)
: m_options(opt),
  nodes_count { },
  nodes_reopen { }
{
    std::cout << "Running PAStar with: "
              << opt.threads_num << " threads, "
              << Coord<N>::get_hash_name() << " hash, "
              << Coord<N>::get_hash_shift() << " shift.\n";

    end_cond = false;
    sync_count = 0;
    final_node.set_max();

    OpenList = new PriorityList<N>[m_options.threads_num]();
    ClosedList = new std::map< Coord<N>, Node<N> >[m_options.threads_num]();

    nodes_count = new long long int[m_options.threads_num]();
    nodes_reopen = new long long int[m_options.threads_num]();

    queue_mutex = new std::mutex[m_options.threads_num]();
    queue_condition = new std::condition_variable[m_options.threads_num]();
    queue_nodes = new std::vector< Node<N> >[m_options.threads_num]();

    // Enqueue first node
    OpenList[0].enqueue(node_zero);
}

template < int N >
PAStar<N>::~PAStar()
{
    delete[] OpenList;
    delete[] ClosedList;
    delete[] nodes_count;
    delete[] nodes_reopen;
    delete[] queue_mutex;
    delete[] queue_condition;
    delete[] queue_nodes;
}

template < int N >
int PAStar<N>::set_affinity(int tid)
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
template < int N >
void PAStar<N>::enqueue(int tid, std::vector< Node<N> > &nodes)
{
    typename std::map< Coord<N>, Node<N> >::iterator c_search;

    for (typename std::vector< Node<N> >::iterator it = nodes.begin() ; it != nodes.end(); ++it)
    {
        if ((c_search = ClosedList[tid].find(it->pos)) != ClosedList[tid].end())
        {
            if (it->get_g() >= c_search->second.get_g())
                continue;
            ClosedList[tid].erase(it->pos);
            nodes_reopen[tid] += 1;
        }
        //std::cout << Adding:\t" << *it << std::endl;
        OpenList[tid].conditional_enqueue(*it);
    }
    return;
}

//! Consume the queue with id \a tid
template < int N >
void PAStar<N>::consume_queue(int tid)
{
    std::unique_lock<std::mutex> queue_lock(queue_mutex[tid]);
    std::vector< Node<N> > nodes_to_expand(queue_nodes[tid]);
    queue_nodes[tid].clear();
    queue_lock.unlock();

    enqueue(tid, nodes_to_expand);
    return;
}

//! Wait something on the queue
template < int N >
void PAStar<N>::wait_queue(int tid)
{
    std::unique_lock<std::mutex> queue_lock(queue_mutex[tid]);
    if (queue_nodes[tid].size() == 0)
        queue_condition[tid].wait(queue_lock);
    return;
}

//! Wake up everyone waiting on the queue
template < int N >
void PAStar<N>::wake_all_queue()
{
    for (int i = 0; i < m_options.threads_num; ++i)
    {
        std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
        queue_condition[i].notify_one();
    }
    return;
}

//! Sync all threads
template < int N >
void PAStar<N>::sync_threads()
{
    std::unique_lock<std::mutex> sync_lock(sync_mutex);
    if (++sync_count < m_options.threads_num)
        sync_condition.wait(sync_lock);
    else
    {
        sync_count = 0;
        sync_condition.notify_all();
    }
}

//! Execute the pa_star algorithm until all nodes expand the same final node
template < int N >
void PAStar<N>::worker_inner(int tid, const Coord<N> &coord_final)
{
    Node<N> current;
    std::vector< Node<N> > neigh[m_options.threads_num];

    // Loop ended by process_final_node
    while (end_cond == false)
    {
        typename std::map< Coord<N>, Node<N> >::iterator c_search;

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
            if (current.get_g() >= c_search->second.get_g())
                continue;
            nodes_reopen[tid] += 1;
        }

        //std::cout << "[" << tid << "] Opening node:\t" << current << std::endl;
        ClosedList[tid][current.pos] = current;

        if (current.pos == coord_final)
        {
            process_final_node(tid, current);
            continue;
        }

        // Expand phase
        current.getNeigh(neigh, m_options.threads_num);

        // Reconciliation phase
        for (int i = 0; i < m_options.threads_num; i++)
        {
            if (i == tid)
                enqueue(tid, neigh[i]);
            else if (neigh[i].size() != 0)
            {
                std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
                queue_nodes[i].insert(queue_nodes[i].end(), neigh[i].begin(), neigh[i].end());
                queue_condition[i].notify_one();
            }
            neigh[i].clear();
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
template < int N >
void PAStar<N>::process_final_node(int tid, const Node<N> &n)
{
    std::unique_lock<std::mutex> final_node_lock(final_node_mutex);

    // Better possible answer already found, discard n
    if (final_node.get_f() < n.get_f())
        return;

    if (n.pos.get_id(m_options.threads_num) == (unsigned int)tid)
    {
        //std::cout << "[" << tid << "] Possible answer found: " << n << std::endl;
        // Broadcast the node
        final_node = n;
        final_node_count = 0;
        final_node_lock.unlock();

        for (int i = 0; i < m_options.threads_num; i++)
        {
            if (i != tid)
            {
                std::unique_lock<std::mutex> queue_lock(queue_mutex[i]);
                queue_nodes[i].push_back(n);
                queue_condition[i].notify_one();
            }
        }
    }
    else
    {
       //std::cout << "[" << tid << "] Agreed with possible answer! " << n << "/" << final_node << std::endl;
       //if (n != final_node) std::cout << "BUG HERE!\n";
       final_node_lock.unlock();
    }

    // Process a broadcast node
    if (++final_node_count == m_options.threads_num)
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
template < int N >
bool PAStar<N>::check_stop(int tid)
{
    wake_all_queue();
    sync_threads();
    Node<N> n = final_node;
    consume_queue(tid);
    if (OpenList[tid].get_highest_priority() < final_node.get_f())
    {
        //std::cout << "[" << tid << "] reporting early end!\n";
        end_cond = false;
    }
    sync_threads();
    if (end_cond == false)
    {
        ClosedList[tid].erase(n.pos);
        if (n.pos.get_id(m_options.threads_num) == (unsigned int)tid)
            OpenList[tid].conditional_enqueue(n);
        return true;
    }
    return false;
}

//! Execute a worker thread. This thread have id \a tid
template < int N >
int PAStar<N>::worker(int tid, const Coord<N> &coord_final)
{
    set_affinity(tid);
    // worker_inner is the main inner loop
    // check_stop syncs and check if is the optimal answer
    do {
        worker_inner(tid, coord_final);
    } while (check_stop(tid));

    return 0;
}

template < int N >
void PAStar<N>::print_nodes_count()
{
    long long int nodes_total = 0;
    long long int open_list_total = 0;
    long long int closed_list_total = 0;
    long long int nodes_reopen_total = 0;

    std::cout << "Total nodes count:" << std::endl;
    for (int i = 0; i < m_options.threads_num; ++i)
    {
        std::cout << "tid " << i
             << "\tOpenList:" << OpenList[i].size()
             << "\tClosedList:" << ClosedList[i].size()
             << "\tReopen:" << nodes_reopen[i]
             << "\tTotal: " << nodes_count[i] << std::endl;
        open_list_total += OpenList[i].size();
        closed_list_total += ClosedList[i].size();
        nodes_reopen_total += nodes_reopen[i];
        nodes_total += nodes_count[i];
    }
    std::cout << "Sum"
          << "\tOpenList:" << open_list_total
          << "\tClosedList:" << closed_list_total
          << "\tReopen:" << nodes_reopen_total
          << "\tTotal: " << nodes_total << std::endl;
}

template < int N >
void PAStar<N>::print_answer()
{
    backtrace<N>(ClosedList, m_options.threads_num);
    print_nodes_count();
}

/*!
 * Same a_star() function usage.
 * Starting function to do a pa_star search.
 */
template < int N >
int PAStar<N>::pa_star(const Node<N> &node_zero, const Coord<N> &coord_final, const PAStarOpt &options)
{
    if (options.threads_num <= 0)
        throw std::invalid_argument("Invalid number of threads");
    Coord_configure_hash(options.hash_type, options.hash_shift);

    PAStar<N> pastar_instance(node_zero, options);
    std::vector<std::thread> threads;
    TimeCounter *t = new TimeCounter("Phase 2: PA-Star running time: ");

    // Create threads
    for (int i = 0; i < options.threads_num; ++i)
        threads.push_back(std::thread(&PAStar::worker, &pastar_instance, i, coord_final));

    // Wait for the end of all threads
    for (auto& th : threads)
        th.join();
    delete t;
    pastar_instance.print_answer();

    if (options.common_options.force_quit)
        exit(0);
    return 0;
}

#define PASTAR_DECLARE_TEMPLATE( X ) \
template class PAStar< X >; \

MAX_NUM_SEQ_HELPER(PASTAR_DECLARE_TEMPLATE);

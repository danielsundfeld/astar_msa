#ifndef _PSTAR_H
#define _PSTAR_H
/*!
 * \class PAStar
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Do a multiple sequence alignment reducing the search space
 * with parallel a-star algorithm
 */
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "Coord.h"
#include "Node.h"
#include "PriorityList.h"

#define search_function pa_star

const std::string initial_message("Performing search with Parallel A-Star.\n");

#ifndef THREADS_NUM
    #define THREADS_NUM 4
#endif

template < int N >
class PAStar {
    private:
        // Members
        PriorityList<N> OpenList[THREADS_NUM];
        std::map< Coord<N>, Node<N> > ClosedList[THREADS_NUM];

        long long int nodes_count[THREADS_NUM];
        long long int nodes_reopen[THREADS_NUM];

        std::mutex queue_mutex[THREADS_NUM];
        std::condition_variable queue_condition[THREADS_NUM];
        std::vector< Node<N> > queue_nodes[THREADS_NUM];

        std::atomic<bool> end_cond;

        std::mutex final_node_mutex;
        Node<N> final_node;
        std::atomic<int> final_node_count;

        std::mutex sync_mutex;
        std::atomic<int> sync_count;
        std::condition_variable sync_condition;

        // Constructor
        PAStar(const Node<N> &node_zero);

        // Misc functions
        int set_affinity(int tid);
        void sync_threads();
        void print_nodes_count();

        // Queue functions
        void enqueue(int tid, std::vector< Node<N> > &nodes);
        void consume_queue(int tid);
        void wait_queue(int tid);
        void wake_all_queue();

        // End functions
        void process_final_node(int tid, const Node<N> &n);
        bool check_stop(int tid);

        // Worker Functions
        void worker_inner(int tid, bool(*is_final)(const Coord<N> &c));
        int worker(int tid, bool(*is_final)(const Coord<N> &c));

        // Backtrack
        void print_answer();

    public:
        static int pa_star(const Node<N> &node_zero, bool(*is_final)(const Coord<N> &c));
};
#endif

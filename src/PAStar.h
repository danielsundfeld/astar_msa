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
#include "Coord.h"
#include "Node.h"

#define search_function pa_star

const string initial_message("Performing search with Parallel A-Star.\n");

#ifndef THREADS_NUM
    #define THREADS_NUM 4
#endif

class PAStar {
    private:
        PAStar();

        // Misc functions
        int set_affinity(int tid);
        void sync_threads();
        void print_nodes_count();

        // Queue functions
        void enqueue(int tid, std::vector<Node> &nodes);
        void consume_queue(int tid);
        void wait_queue(int tid);
        void wake_all_queue();

        // End functions
        void process_final_node(int tid, const Node &n);
        bool check_stop(int tid);

        // Worker Functions
        void worker_inner(int tid, bool(*is_final)(const Coord &c));
        int worker(int tid, bool(*is_final)(const Coord &c));

    public:
        static int pa_star(const Node &node_zero, bool(*is_final)(const Coord &c));
};
#endif

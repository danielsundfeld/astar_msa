/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef _ASTAR_H
#define _ASTAR_H
#include <string>

#include "Coord.h"
#include "Node.h"

struct AStarOpt {
    /*!
     * Calling all destructors in the OpenList and the Global Memory might be
     * really time consuming. If only one alignment is done, we might exit(0)
     * and save some time. This option may be changed for memcheck purposes.
     */
    bool force_quit;
    std::string fasta_output_file;

    AStarOpt()
    {
        force_quit = true;
        fasta_output_file = "";
    }
    AStarOpt(bool force)
    {
        force_quit = force;
        fasta_output_file = "";
    }
};

template <int N> int a_star(const Node<N> &node_zero, const Coord<N> &coord_final, const AStarOpt &options);
#endif

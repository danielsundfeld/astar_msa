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

    AStarOpt()
    {
        force_quit = true;
    }
    AStarOpt(bool force)
    {
        force_quit = force;
    }
};

template <int N> int a_star(const Node<N> &node_zero, const Coord<N> &coord_final, const AStarOpt &options);
#endif

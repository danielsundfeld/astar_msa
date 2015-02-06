/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Do a multiple sequence alignment reducing the search space
 * with a-star algorithm alignment
 */
#include <iostream>
#include <vector>

#include "AStar.h"
#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "PriorityList.h"
#include "TimeCounter.h"

/*!
 * A classic A-Star implentation resume:
 *
 * OPEN = priority queue with START node
 * CLOSED = empty
 *
 * while lowest rank in OPEN is not the GOAL:
 * current = remove lowest rank item from OPEN
 * add current to CLOSED
 * for neighbors of current:
 *   cost = g(current) + movementcost(current, neighbor)
 *   if neighbor in OPEN and cost less than g(neighbor):
 *     remove neighbor from OPEN, because new path is better
 *   if neighbor in CLOSED and cost less than g(neighbor):
 *     remove neighbor from CLOSED
 *   if neighbor not in OPEN and neighbor not in CLOSED:
 *     set g(neighbor) to cost
 *     add neighbor to OPEN
 *     set priority queue rank to g(neighbor) + h(neighbor)
 *     set neighbor's parent to current
 */
template <int N>
int a_star(const Node<N> &node_zero, const Coord<N> &coord_final, const AStarOpt &options)
{
    Node<N> current;
    PriorityList<N> OpenList;
    std::map< Coord<N>, Node<N> > ClosedList;
    std::vector< Node<N> > neigh;
    TimeCounter t("\nPhase 2: A-Star running time: ");

    OpenList.enqueue(node_zero);

    while (!OpenList.empty())
    {
        typename std::map< Coord<N>, Node<N> >::iterator c_search;

        OpenList.dequeue(current);

        // Check if better node is already found
        if ((c_search = ClosedList.find(current.pos)) != ClosedList.end())
        {
            if (current.get_g() >= c_search->second.get_g())
                continue;
        }

        //std::cout << "Opening node:\t" << current << std::endl;
        ClosedList[current.pos] = current;

        if (current.pos == coord_final)
            break;

        current.getNeigh(&neigh);
        for (typename std::vector< Node<N> >::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        {
            if ((c_search = ClosedList.find(it->pos)) != ClosedList.end())
            {
                if (it->get_g() >= c_search->second.get_g())
                    continue;
                ClosedList.erase(it->pos);
            }

            OpenList.conditional_enqueue(*it);
            //std::cout << "Adding:\t" << *it << "from\t" << current << std::endl;
        }
        neigh.clear();
    }
    backtrace<N>(&ClosedList, 1);

    if (options.force_quit)
        exit(0);
    return 0;
}

#define A_STAR_DECLARE_TEMPLATE( X ) \
template int a_star< X >(const Node< X > &node_zero, const Coord< X > &coord_final, const AStarOpt &options); \

MAX_NUM_SEQ_HELPER(A_STAR_DECLARE_TEMPLATE);

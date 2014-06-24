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
int a_star(const Node<N> &node_zero, bool(*is_final)(const Coord<N> &c))
{
    Node<N> current;
    PriorityList<N> OpenList;
    std::map< Coord<N>, Node<N> > ClosedList;
    std::vector< Node<N> > neigh;

    OpenList.enqueue(node_zero);

    while (!OpenList.empty())
    {
        typename openlist_multiindex<N>::type::iterator o_search;
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

        if (is_final(current.pos))
            break;

        neigh.clear();
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
    }
    backtrace<N>(&ClosedList, 1);
    return 0;
}

#define A_STAR_DECLARE_TEMPLATE( X ) \
template int a_star< X >(const Node< X > &node_zero, bool(*is_final)(const Coord< X > &c)); \

MAX_NUM_SEQ_TEMPLATE_HELPER(A_STAR_DECLARE_TEMPLATE);

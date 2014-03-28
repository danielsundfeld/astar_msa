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

using namespace std;

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
int a_star(const Node &node_zero, bool(*is_final)(const Coord &c))
{
    Node current;
    PriorityList OpenList;
    ListType ClosedList;

    OpenList.enqueue(node_zero);

    while (!OpenList.empty())
    {
        open_list_iterator o_search;
        closed_list_iterator c_search;

        OpenList.dequeue(current);

        // Check if better node is already found
        if ((o_search = OpenList.find(current.pos)) != OpenList.end())
        {
            if (current.get_g() > open_list_return_g(o_search))
                continue;
        }
        // Or already opened
        if ((c_search = ClosedList.find(current.pos)) != ClosedList.end())
        {
            if (current.get_g() >= closed_list_return_g(c_search))
                continue;
        }

        //cout << "Opening node:\t" << current << endl;
        ClosedList[current.pos] = current;

        if (is_final(current.pos))
            break;

        OpenList.verifyMemory();

        vector<Node> neigh;
        current.getNeigh(&neigh);
        for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
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

            OpenList.enqueue(*it);
            //cout << "Adding:\t" << *it << "from\t" << current << endl;
        }
    }
    cout << "Final score:\t" << current << endl;
    backtrace(&ClosedList);
    return 0;
}

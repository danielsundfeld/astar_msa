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
int a_star(const Coord &coord_zero, const Node &node_zero, bool(*is_final)(const Coord &c))
{
    Node current;
    PriorityList OpenList;
    ListType ClosedList;

    OpenList.enqueue(coord_zero, node_zero);

    while (!OpenList.empty())
    {
        ListType::const_iterator search;

        OpenList.dequeue(current);

       // Check if better node is already found
        if ((search = OpenList.find(current.pos)) != OpenList.end())
        {
            if (current.get_g() > search->second.get_g())
                continue;
        }
        // Or already opened
        if ((search = ClosedList.find(current.pos)) != ClosedList.end())
        {
            if (current.get_g() >= search->second.get_g())
                continue;
        }

        //cout << "Opening node:\t" << current << endl;
        OpenList.erase(current.pos);
        ClosedList[current.pos] = current;

        if (is_final(current.pos))
            break;

        OpenList.verifyMemory();

        vector<Node> neigh;
        current.getNeigh(neigh);
        for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        {
            if ((search = OpenList.find(it->pos)) != OpenList.end())
            {
                // if score on open list is better, ignore this neighboor
                if (it->get_g() > search->second.get_g())
                    continue;
            }
            if ((search = ClosedList.find(it->pos)) != ClosedList.end())
            {
                if (it->get_g() >= search->second.get_g())
                    continue;
                ClosedList.erase(it->pos);
            }

            OpenList.enqueue(it->pos, *it);
            //cout << "Adding:\t" << *it << "from\t" << current << endl;
        }
    }
    cout << "Final score:\t" << current << endl;
    backtrace(ClosedList);
    return 0;
}

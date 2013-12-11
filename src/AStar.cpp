#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

/*
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
int a_star()
{
    map<Coord, Node> OpenList;
    map<Coord, Node> ClosedList;
    priority_queue<Node, vector<Node>, PriorityNode> pq;
    Sequences *seq = Sequences::getInstance();

    const Coord coord_zero; //default is zero
    const Node node_zero(0, coord_zero);
    OpenList[coord_zero] = node_zero;
    pq.push(node_zero); //Zero cost, zero coords.

    Node current = pq.top();
    while (!pq.empty() && seq->is_not_final(current.pos))
    {
        //cout << "Opening node:\t" << current << endl;
        pq.pop();
        ClosedList[current.pos] = current;

        vector<Node> neigh;
        current.getNeigh(neigh);

        for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        {
            std::map<Coord,Node>::iterator search;

            if ((search = OpenList.find(it->pos)) != OpenList.end())
            {
                // if score on open list is better, ignore this neighboor
                if (it->get_g() >= search->second.get_g())
                    continue;
            }
            if ((search = ClosedList.find(it->pos)) != ClosedList.end())
            {
                if (it->get_g() >= search->second.get_g())
                    continue;
                ClosedList.erase(it->pos);
            }

            OpenList[it->pos] = *it;
            pq.push(*it);
        }
        current = pq.top();
    }
    ClosedList[current.pos] = current;
    cout << "Final score:\t" << current << endl;
    backtrace(ClosedList);
    return 0;
}


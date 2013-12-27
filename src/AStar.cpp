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
    Node current;
    map<Coord, Node> OpenList;
    map<Coord, Node> ClosedList;
    priority_queue<Node, vector<Node>, PriorityNode> pq;
    Sequences *seq = Sequences::getInstance();

    const Coord coord_zero(0, 0, 0);
    const Node node_zero(0, coord_zero, coord_zero);
    OpenList[coord_zero] = node_zero;
    pq.push(node_zero); //Zero cost, zero coords.

    while (!pq.empty())
    {
        current = pq.top();
        map<Coord,Node>::iterator search;
        pq.pop();

       // Check if better node is already found
        if ((search = OpenList.find(current.pos)) != OpenList.end())
        {
            if (current.get_g() > search->second.get_g())
            {
                current = pq.top();
                continue;
            }
        }
        // Or already opened
        if ((search = ClosedList.find(current.pos)) != ClosedList.end())
        {
            if (current.get_g() >= search->second.get_g())
            {
                current = pq.top();
                continue;
            }
        }

        if (seq->is_final(current.pos))
            break;

        //cout << "Opening node:\t" << current << endl;
        ClosedList[current.pos] = current;

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

            OpenList[it->pos] = *it;
            //cout << "Adding:\t" << *it << "from\t" << current << endl;
            pq.push(*it);
        }
    }
    ClosedList[current.pos] = current;
    cout << "Final score:\t" << current << endl;
    backtrace(ClosedList);
    return 0;
}


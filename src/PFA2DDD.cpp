/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Do a multiple sequence alignment reducing the search space
 * with pfa2ddd algorithm
 */
#include <iostream>
#include <thread>
#include <vector>

#include "AStar.h"
#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "PriorityList.h"

using namespace std;

#define THREADS_NUM 1

/*!
 * Same a_star() function usage
 */
int pfa2ddd_worker(int tid, const Node &node_zero, bool(*is_final)(const Coord &c))
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
        current.getNeigh(neigh);
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
    backtrace(ClosedList);
    return 0;
}

int pfa2ddd(const Node &node_zero, bool(*is_final)(const Coord &c))
{
    std::vector<std::thread> threads;

    for (int i = 0; i < 1; ++i)
        threads.push_back(std::thread(pfa2ddd_worker, i, node_zero, is_final));

    for (auto& th : threads)
        th.join();
    return 0;
}

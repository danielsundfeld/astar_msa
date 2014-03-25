/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Do a multiple sequence alignment reducing the search space
 * with pfa2ddd algorithm
 */
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

#include "AStar.h"
#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "PriorityList.h"
#include "Sequences.h"

using namespace std;

#define THREADS_NUM 1
#define MERGE_NODES_NUM 900000

PriorityList OpenList[THREADS_NUM];

atomic<int> merge_count;
std::condition_variable merge_cond;
std::mutex merge_mutex;

atomic<bool> end_cond;

void pfa2ddd_merge_do()
{
    for (int i = 1; i < THREADS_NUM; ++i)
        OpenList[0].merge(OpenList[i]);

    for (int i = 1; i < THREADS_NUM; ++i)
        OpenList[i] = OpenList[0];

    return;
}

void pfa2ddd_merge_phase(int tid)
{ 
    cout << "Iniciando merge... " << tid << endl;
    std::unique_lock<std::mutex> merge_lock(merge_mutex);
    merge_count++;
    if (tid == 0)
    {
        merge_lock.unlock();
        while (merge_count < THREADS_NUM)
            ;
        pfa2ddd_merge_do();
        merge_count = 0;
        merge_cond.notify_all();
    }
    else
    {
        merge_cond.wait(merge_lock);
    }
    cout << "Terminando merge... " << tid << endl;
    return;
}

/*!
 * Same a_star() function usage
 */
int pfa2ddd_worker(int tid, const Node &node_zero, bool(*is_final)(const Coord &c))
{
    Node current;
    ListType ClosedList;
    int nodes = 0;

    OpenList[tid].enqueue(node_zero);

    while (!OpenList[tid].empty())
    {
        open_list_iterator o_search;
        closed_list_iterator c_search;

        OpenList[tid].dequeue(tid, current);
        nodes++;

        if (nodes == MERGE_NODES_NUM || merge_count)
        {
            nodes = 0;
            pfa2ddd_merge_phase(tid);
            if (end_cond)
                break;
        }
        else if (end_cond)
        {
            pfa2ddd_merge_phase(tid);
            break;
        }

        // Check if better node is already found
        if ((o_search = OpenList[tid].find(current.pos)) != OpenList[tid].end())
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

        if (tid == 0 && is_final(current.pos))
        {
            cout << "MATANDO!\n";
            end_cond = true;
            pfa2ddd_merge_phase(tid);
            break;
        }

        OpenList[tid].verifyMemory();

        vector<Node> neigh;
        current.getNeigh(neigh);
        for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        {
            if ((o_search = OpenList[tid].find(it->pos)) != OpenList[tid].end())
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

            OpenList[tid].enqueue(*it);
            //cout << "Adding:\t" << *it << "from\t" << current << endl;
        }
    }
    if (tid == 0)
        cout << "Final score:\t" << current << endl;
    return 0;
}

int pfa2ddd(const Node &node_zero, bool(*is_final)(const Coord &c))
{
    std::vector<std::thread> threads;

    end_cond = false;
    merge_count = 0;

    for (int i = 0; i < THREADS_NUM; ++i)
        threads.push_back(std::thread(pfa2ddd_worker, i, node_zero, is_final));

    for (auto& th : threads)
        th.join();
    return 0;
}

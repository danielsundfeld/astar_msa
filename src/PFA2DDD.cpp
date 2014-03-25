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

PriorityList OpenList[THREADS_NUM];

atomic<int> merge_count;
std::condition_variable merge_cond;
std::mutex merge_mutex;

atomic<bool> end_cond;

void sync_terminate()
{
    std::unique_lock<std::mutex> merge_lock(merge_mutex);
    end_cond = true;
    merge_cond.notify_all();
}

bool sync_openlist()
{
    std::unique_lock<std::mutex> merge_lock(merge_mutex);
    if (end_cond)
        return false;
    merge_count++;
    if (merge_count == THREADS_NUM)
    {
        merge_count = 0;
        merge_cond.notify_all();
    }
    else
    {
        merge_cond.wait(merge_lock);
        if (end_cond)
            return false;
    }
    return true;
}

bool sync_skip()
{
    for (int i = 0; i < THREADS_NUM; i++)
        if (sync_openlist() == false)
            return false;
    return true;
}

/*!
 * Same a_star() function usage
 */
int pfa2ddd_worker(int tid, const Node &node_zero, bool(*is_final)(const Coord &c))
{
    Node current;
    ListType ClosedList;
    bool last_node = false;

    if (tid == 0)
        OpenList[tid].enqueue(node_zero);

    while (end_cond == false)
    {
        open_list_iterator o_search;
        closed_list_iterator c_search;

        if (sync_openlist() == false)
            break;

        if (OpenList[tid].dequeue(current) == false)
        {
            sync_skip();
            continue;
        }

        // Check if better node is already found
        if ((o_search = OpenList[tid].find(current.pos)) != OpenList[tid].end())
        {
            if (current.get_g() > open_list_return_g(o_search))
            {
                sync_skip();
                continue;
            }
        }
        // Or already opened
        if ((c_search = ClosedList.find(current.pos)) != ClosedList.end())
        {
            if (current.get_g() >= closed_list_return_g(c_search))
            {
                sync_skip();
                continue;
            }
        }

        //cout << "Opening node:\t" << current << endl;
        //cout << "[" << tid << "] Abrindo: " << current << endl;
        ClosedList[current.pos] = current;

        if (is_final(current.pos))
        {
            cout << "MATANDO!\n";
            last_node = true;
            sync_terminate();
            break;
        }

        OpenList[tid].verifyMemory();

        vector<Node> neigh[THREADS_NUM] = {} ;
        current.getNeigh(neigh, THREADS_NUM);
        for (int i = 0; i < THREADS_NUM; i++)
        {
            int j = (tid + i) % THREADS_NUM;
            if (sync_openlist() == false)
                break;
           //cout << "[" << tid << '/' << j << "] Turno\n";
            for (vector<Node>::iterator it = neigh[j].begin() ; it != neigh[j].end(); ++it)
            {
                if ((o_search = OpenList[j].find(it->pos)) != OpenList[j].end())
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
                //cout << "[" << tid << '/' << j << "] Adding:\t" << *it << "from\t" << current << endl;
                OpenList[j].enqueue(*it);
            }
        }
    }
    if (last_node)
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

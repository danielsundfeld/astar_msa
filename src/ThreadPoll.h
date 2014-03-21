/*!
 * \ingroup ThreadPoll
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief A threadpoll
 */
#ifndef _THREADPOLL_H
#define _THREADPOLL_H
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

static vector<thread> threads;

template<typename... Args>
static void thread_poll(int th_num, Args... args)
{
    for (int i = 0; i < th_num; i++)
        threads.push_back(thread(args...));
}

static void thread_poll_wait()
{
    for (auto& th : threads)
        th.join();
}
#endif

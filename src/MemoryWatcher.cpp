/*!
 * \filename MemoryWatcher.cpp
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <signal.h>
#include <unistd.h>

#include "Cost.h"
#include "MemoryWatcher.h"
#include "Node.h"

using namespace std;

bool MemoryWatcher::doMemoryClean = false;

void handler(int sig)
{
    MemoryWatcher::setMemoryClean(true);
}

MemoryWatcher::MemoryWatcher()
{
    struct sigaction sig;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = handler;
    sigaction(SIGALRM, &sig, NULL);

    alarm(CleanTime);
}

void MemoryWatcher::performMemoryClean(ListType &openList, PriorityType* &pq)
{
    cout << "Cleaning Memory... " << pq->size() - openList.size() << " nodes. (" << pq->size() << " " << openList.size() << ")" << flush;
    doMemoryClean = false;

    delete pq;
    pq = new PriorityType();
    for (auto it = openList.begin(); it != openList.end(); ++it)
        pq->push(it->second);

    alarm(CleanTime);
    cout << " done!\n";
    return;
}

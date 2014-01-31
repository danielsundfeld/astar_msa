/*!
 * \class MemoryWatcher
 * \filename MemoryWatcher.h
 * \author Daniel Sundfeld
 *
 * \brief Class to clean memory sometimes
 *
 * INSERT_LICENSE
 */
#ifndef _MEMORYWATCHER_H
#define _MEMORYWATCHER_H
#include "AStar.h"

using namespace std;

class MemoryWatcher {
    private:
        static bool doMemoryClean;
        enum { CleanTime = 60 };

    public:
        MemoryWatcher();
        static inline bool getMemoryClean() { return doMemoryClean; };
        static inline void setMemoryClean(bool v) { doMemoryClean = v; };
        void performMemoryClean(ListType &openList, PriorityType* &pq);
};
#endif
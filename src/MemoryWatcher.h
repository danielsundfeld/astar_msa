/*!
 * \class MemoryWatcher
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class to clean memory sometimes
 */
#ifndef _MEMORYWATCHER_H
#define _MEMORYWATCHER_H
#include "PriorityTypes.h"

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

/*!
 * \class MemoryWatcher
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class to clean memory sometimes
 *
 * This class does not makes sense on libboost implementation and should
 * not be used
 */
#ifndef _MEMORYWATCHER_H
#define _MEMORYWATCHER_H
#ifdef NO_LIB_BOOST // Memory Watcher only used on STL implementation
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
#endif // NO_LIB_BOOST
#endif // _MEMORYWATCHER_H

/*!
 * \class PerformanceReport
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Report time, memory usage and space reductin
 */
#ifndef _PERFORMANCE_REPORT_H
#define _PERFORMANCE_REPORT_H
#include "PriorityTypes.h"

using namespace std;

class PerformanceReport {
    private:
        const ListType * const m_OpenList;
        const ListType * const m_ClosedList;
        struct timeval m_start;

        void SpaceReduction();
        void TimeElapsed();
    public:
        PerformanceReport(ListType *OpenList, ListType *ClosedList);
        ~PerformanceReport();
};
#endif

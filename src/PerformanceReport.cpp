/*!
 * \class PerformanceReport
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <iostream>
#include <limits>
#include <sys/time.h>

#include "Coord.h"
#include "Node.h"
#include "PerformanceReport.h"
#include "PriorityTypes.h"
#include "Sequences.h"

using namespace std;

PerformanceReport::PerformanceReport(ListType *OpenList, ListType *ClosedList)
: m_OpenList(OpenList),
  m_ClosedList(ClosedList)
{
    gettimeofday(&m_start, NULL);
}

PerformanceReport::~PerformanceReport()
{
    SpaceReduction();
    TimeElapsed();
}

void PerformanceReport::TimeElapsed()
{
    struct timeval m_end;
    gettimeofday(&m_end, NULL);

    cout.precision(2);
    cout << "Elapsed time: " <<
        ((m_end.tv_usec - m_start.tv_usec)) / 1000000.0f << "s.\n";
}

void PerformanceReport::SpaceReduction()
{
    cout.precision(std::numeric_limits< double >::digits10);
    cout << "Expanded nodes: " << m_OpenList->size() + m_ClosedList->size() << ". ";
    double size = m_OpenList->size() + m_ClosedList->size();
    size *= 100; // size in %

    for (unsigned int i = 0; i < Sequences::get_seq_num(); i++)
        size /= (Sequences::get_final_coord()[i] + 1);

    cout << "Space reduction of: ";
    if (size < 0.0000000001)
        cout << ">99.9999999999%\n";
    else
        cout << " " << 100 - size << "%\n";
}

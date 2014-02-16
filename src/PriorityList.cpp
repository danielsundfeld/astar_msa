/*!
 * \class PriorityList
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "PriorityList.h"

using namespace std;

PriorityList::PriorityList()
{
    m_pq = new PriorityType();
}

PriorityList::~PriorityList()
{
    delete m_pq;
}

const ListType::mapped_type& PriorityList::enqueue(const Coord &c, const Node &n)
{
    m_pq->push(n);
    return m_openlist[c] = n;
}

void PriorityList::verifyMemory()
{
    if (m_memwatch.getMemoryClean())
        m_memwatch.performMemoryClean(m_openlist, m_pq);
    return;
}

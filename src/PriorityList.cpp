/*!
 * \class PriorityList
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef NO_LIB_BOOST
 #include <boost/multi_index_container.hpp>
 #include <boost/multi_index/member.hpp>
 #include <boost/multi_index/ordered_index.hpp>
#endif

#include "PriorityList.h"

using namespace std;

int closed_list_return_g(closed_list_iterator search)
{
    return search->second.get_g();
}
#ifdef NO_LIB_BOOST
PriorityList::PriorityList()
{
    m_pq = new PriorityType();
}

PriorityList::~PriorityList()
{
    delete m_pq;
}

const ListType::mapped_type& PriorityList::enqueue(const Node &n)
{
    m_pq->push(n);
    return m_openlist[n.pos] = n;
}

void PriorityList::verifyMemory()
{
    if (m_memwatch.getMemoryClean())
        m_memwatch.performMemoryClean(m_openlist, m_pq);
    return;
}

int open_list_return_g(list_type_iterator search)
{
    return search->second.get_g();
}
#else
void PriorityList::dequeue(Node &n)
{
    auto it = get<priority>(m_openlist).begin();
    n = *it;
    m_openlist.erase(it->pos);
}

bool PriorityList::enqueue(const Node &c)
{
    openlist_multiindex::index<pos>::type::iterator it = m_openlist.find(c.pos);
    if (it == m_openlist.end())
        return m_openlist.insert(c).second;
    return m_openlist.modify(it, change_node(c.get_f(), c.get_g(), c.get_parenti()));
}

int open_list_return_g(list_type_iterator search)
{
    return search->get_g();
}
#endif //NO_LIB_BOOST

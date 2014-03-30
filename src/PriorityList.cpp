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

int open_list_return_g(open_list_iterator search)
{
    return search->second.get_g();
}
#else
bool PriorityList::dequeue(Node &n)
{
    auto it = get<priority>(m_openlist).begin();
    if (it == get<priority>(m_openlist).end())
        return false;
    n = *it;
    m_openlist.erase(it->pos);
    return true;
}

bool PriorityList::enqueue(const Node &c)
{
    openlist_multiindex::index<pos>::type::iterator it = m_openlist.find(c.pos);
    if (it == m_openlist.end())
        return m_openlist.insert(c).second;
    return m_openlist.modify(it, change_node(c.get_f(), c.get_g(), c.get_parenti()));
}

bool PriorityList::conditional_enqueue(const Node &c)
{
    openlist_multiindex::index<pos>::type::iterator it = m_openlist.find(c.pos);
    if (it == m_openlist.end())
        return m_openlist.insert(c).second;
    if (c.get_f() >= it->get_f())
        return true;
    return m_openlist.modify(it, change_node(c.get_f(), c.get_g(), c.get_parenti()));
}

void PriorityList::merge(const PriorityList& other)
{
    auto it = get<priority>(other.m_openlist).begin();
    while (it != get<priority>(other.m_openlist).end())
    {
        conditional_enqueue(*it);
        ++it;
    }
    return; 
}

int open_list_return_g(open_list_iterator search)
{
    return search->get_g();
}

#endif //NO_LIB_BOOST
/*!
 * \class PriorityList
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class that implements an Heuristic Search OpenList
 */
#ifndef _PRIORITY_LIST
#define _PRIORITY_LIST
#ifdef NO_LIB_BOOST
 #include <map>
 #include <queue>
#else
 #include <boost/multi_index_container.hpp>
 #include <boost/multi_index/member.hpp>
 #include <boost/multi_index/ordered_index.hpp>
#endif

#include "Coord.h"
#include "MemoryWatcher.h"
#include "Node.h"
#include "PriorityTypes.h"

using namespace std;

#ifdef NO_LIB_BOOST
typedef ListType::const_iterator open_list_iterator;

class PriorityList {
    private:
        MemoryWatcher m_memwatch;
        ListType m_openlist;
        PriorityType *m_pq;

    public: 
        PriorityList();
        ~PriorityList();

        bool dequeue(Node &n);
        const ListType::mapped_type& enqueue(const Node &n);
        int get_highest_priority() const;
        void verifyMemory();

        open_list_iterator find(const Coord &c) const { return m_openlist.find(c); };
        open_list_iterator end() const { return m_openlist.end(); };
        ListType::size_type erase(const Coord &c) { return m_openlist.erase(c); };
        size_t size(void) { return m_openlist.size(); };

        void pop() { return m_pq->pop(); };
        const PriorityType::value_type& top() const { return m_pq->top(); };
        bool empty() const { return m_pq->empty(); };
};
#else
using boost::multi_index_container;
using namespace boost::multi_index;

struct pos{};
struct priority{};

typedef multi_index_container<
    Node,
    indexed_by<
        ordered_unique<
              tag<pos>,  BOOST_MULTI_INDEX_MEMBER(Node,Coord,pos)>,
        ordered_non_unique<
              tag<priority>, BOOST_MULTI_INDEX_MEMBER(Node,int,m_f)> >
> openlist_multiindex;

typedef openlist_multiindex::const_iterator open_list_iterator;

class PriorityList {
    private:
        openlist_multiindex m_openlist;

    public: 
        bool dequeue(Node &n);
        bool enqueue(const Node &n);
        bool conditional_enqueue(const Node &n);
        int get_highest_priority() const;
        void verifyMemory() { return; };

        open_list_iterator find(const Coord &c) const { return m_openlist.find(c); };
        open_list_iterator end() const { return m_openlist.end(); };
        openlist_multiindex::size_type  erase(const Coord &c) { return m_openlist.erase(c); };
        size_t size(void) { return m_openlist.size(); };

        bool empty() { return m_openlist.empty(); };

        void merge(const PriorityList& other);
};
#endif //NO_LIB_BOOST

int closed_list_return_g(closed_list_iterator search);
int open_list_return_g(open_list_iterator search);
#endif

/*!
 * \class PriorityList
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class that implements an Heuristic Search OpenList
 */
#ifndef _PRIORITY_LIST
#define _PRIORITY_LIST
#include <map>
#include <queue>

#include "Coord.h"
#include "MemoryWatcher.h"
#include "Node.h"

using namespace std;

typedef map<Coord, Node> ListType;
typedef priority_queue<Node, vector<Node>, PriorityNode> PriorityType;

class PriorityList {
    private:
        MemoryWatcher m_memwatch;
        ListType m_openlist;
        PriorityType *m_pq;

    public: 
        PriorityList();
        ~PriorityList();

        const ListType::mapped_type& enqueue(const Node &n);
        void verifyMemory();

        ListType::const_iterator find(const Coord &c) const { return m_openlist.find(c); };
        ListType::const_iterator end() const { return m_openlist.end(); };
        ListType::size_type erase(const Coord &c) { return m_openlist.erase(c); };

        void pop() { return m_pq->pop(); };
        const PriorityType::value_type& top() { return m_pq->top(); };
        bool empty() { return m_pq->empty(); };

        void dequeue(PriorityType::value_type& c) { c = top(); erase(c.pos); return pop(); };
};
#endif

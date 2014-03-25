/*!
 * \class Node
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class that hold all Nodes atributes, like the cost from the
 * origin, heuristic estimative, parent
 */
#ifndef _NODE_H
#define _NODE_H
#include <vector>
#include "Coord.h"

using namespace std;

class Node {
    friend class PriorityNode;
    friend class change_node;
    private:
        int m_g; //!< exact cost of the path from the start
        int parenti; //!< Integer representing the parent
        bool borderCheck(const Coord &c) const;
        inline int bitSeq(const int &i) const;
        inline bool bitSeqCheck(const int &i, const int &s1, const int &s2) const;
        inline bool bitSeqCheck(const int &i, const int &s1) const;
        inline int pairCost(const int &neigh_num, const int &mm_cost, const int &s1, const int &s2) const;

    public: 
        int m_f; //!< priority
        Coord pos; //!< Multidimensional coordinate of the node
        Node();
        Node(const int g, const Coord &pos, const int &parenti);
        friend ostream &operator<<(ostream &lhs, const Node &rhs);
        int getNeigh(vector<Node> a[], int vec_size);
        int get_g() const { return m_g; };
        int get_f() const { return m_f; };
        int get_h() const { return m_f - m_g; }; //!< heuristc estimated cost to the goal
        int get_parenti() const { return parenti; };
        inline Coord get_parent() const { return pos.parent(parenti); };
};

#ifndef NO_LIB_BOOST
/*!
 * On an "update" operation, Coord always have the same value and must
 * not be updated.
 */
struct change_node
{
    change_node(int new_f, int new_g, int new_parenti):new_f(new_f), new_g(new_g), new_parenti(new_parenti){}

    void operator()(Node &n)
    {
        n.m_f = new_f;
        n.m_g = new_g;
        n.parenti = new_parenti;
    }
    private:
        int new_f;
        int new_g;
        int new_parenti;
};
#endif

/*!
 * \brief Class to compare Nodes on a priority_queue
 */
class PriorityNode {
    public:
        bool operator()(Node& n1, Node& n2);
};
#endif

/*!
 * \class Node
 * \filename Node.h
 * \author Daniel Sundfeld
 * \brief Class that hold all Nodes atributes, like the cost from the
 * origin, heuristic estimative, parent
 *
 * INSERT_LICENSE
 */
#ifndef _NODE_H
#define _NODE_H
#include <vector>
#include "Coord.h"

using namespace std;

class Node {
    friend class PriorityNode;
    private:
        int m_g; //!< exact cost of the path from the start
        int m_f; //!< priority
        int parenti; //!< Integer representing the parent
        bool borderCheck(const Coord &c) const;
        inline int bitSeq(const int &i) const;
        inline bool bitSeqCheck(const int &i, const int &s1, const int &s2) const;
        inline bool bitSeqCheck(const int &i, const int &s1) const;
        inline int pairCost(const Coord &son, const int &neigh_num, const int &mm_cost, const int &s1, const int &s2) const;

    public: 
        Coord pos; //!< Multidimensional coordinate of the node
        Node();
        Node(const int g, const Coord &pos, const int &parenti);
        friend ostream &operator<<(ostream &lhs, const Node &rhs);
        int getNeigh(vector<Node> &a);
        int get_g() const { return m_g; };
        int get_f() const { return m_f; };
        int get_h() const { return m_f - m_g; }; //!< heuristc estimated cost to the goal
        inline Coord get_parent() const { return pos.parent(parenti); };
};

/*!
 * \brief Class to compare Nodes on a priority_queue
 */
class PriorityNode {
    public:
        bool operator()(Node& n1, Node& n2);
};
#endif

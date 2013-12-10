#ifndef _NODE_H
#define _NODE_H
#include <vector>
#include "Coord.h"

using namespace std;

class Node {
    friend class PriorityNode;
    private:
        int m_g; // exact cost of the path from the start
        int m_h; // heuristc estimated cost to the goal
        int m_f; // priority
        Coord parent;
        void calculate_h();

    public: 
        Coord pos;
        Node();
        Node(const int g, const Coord& pos, const Coord& parent = Coord());
        friend ostream &operator<<(ostream &lhs, const Node &rhs);
        vector<Node> getNeigh();
        int get_g() const { return m_g; };
        int get_f() const { return m_f; };
        int get_h() const { return m_h; };
        inline Coord get_parent() const { return parent; };
};

class PriorityNode {
    public:
        bool operator()(Node& n1, Node& n2);
};
#endif

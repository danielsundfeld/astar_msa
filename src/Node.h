#ifndef _NODE_H
#define _NODE_H
#include "Coord.h"

class Node {
    private:
        int m_g; // exact coast of the path from the start
        int m_h; // Heuristc estimated cost to the goal
        int m_f; // priority

    public: 
        Coord pos;
        Node(const int g, const int f, const int h, const Coord& pos);
        int get_g() { return m_g; };
        int get_f() { return m_f; };
        int get_h() { return m_h; };
};

class PriorityNode {
    public:
        bool operator()(Node& n1, Node& n2)
        {
            if (n1.get_f() < n2.get_f()) return true;
            return false;
        }
};
#endif

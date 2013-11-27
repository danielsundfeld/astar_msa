#ifndef _NODE_H
#define _NODE_H
#include <vector>
#include "Coord.h"

using namespace std;

class Node {
    private:
        int m_g; // exact cost of the path from the start
        int m_h; // heuristc estimated cost to the goal
        int m_f; // priority
        void calculate_h();

    public: 
        Coord pos;
        Node();
        Node(const int g, const Coord& pos);
        vector<Node> getNeigh();

        int get_g() { return m_g; };
        int get_f() { return m_f; };
        int get_h() { return m_h; };
};

class PriorityNode {
    public:
        bool operator()(Node& n1, Node& n2)
        {
            if (n1.get_f() > n2.get_f()) return true;
            return false;
        }
};
#endif

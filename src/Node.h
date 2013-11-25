#ifndef _NODE_H
#define _NODE_H
#include "Coord.h"

class Node {
    private:
        int m_g, m_f, m_h;
        Coord pos;

    public: 
        Node(const int g, const int f, const int h, const Coord& pos);

        int get_g() { return m_g; };
        int get_f() { return m_f; };
        int get_h() { return m_h; };
};

#endif

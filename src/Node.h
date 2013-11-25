#ifndef _NODE_H
#define _NODE_H
#include "Coords.h"

class Node {
    private:
        int m_g, m_f, m_h;
        Coords pos;

    public: 
        Node(const int g, const int f, const int h, const Coords& pos);

        int get_g() { return m_g; };
        int get_f() { return m_f; };
        int get_h() { return m_h; };
};

#endif

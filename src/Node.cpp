#include "Node.h"

Node::Node()
{
    m_g = 0;
    m_f = 0;
    m_h = 0;
}

Node::Node(const int g, const int f, const int h, const Coord& pos)
: pos(pos)
{
    m_g = g;
    m_f = f;
    m_h = h;
}

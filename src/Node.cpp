#include "Node.h"

Node::Node(const int g, const int f, const int h, const Coord& pos)
: pos(pos)
{
    m_g = g;
    m_f = f;
    m_h = h;
}

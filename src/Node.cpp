#include "Node.h"

Node::Node()
{
    m_g = 0;
    m_f = 0;
    m_h = 0;
}

Node::Node(const int g, const Coord& pos)
: pos(pos)
{
    m_g = g;
    m_f = 0; //TODO to calculate
    m_h = 0; //TODO to calculate
}

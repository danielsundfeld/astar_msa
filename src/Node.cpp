#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>

#include "Node.h"
#include "Sequences.h"

using namespace std;

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

vector<Node> Node::getNeigh()
{
    vector<Node> a;
    int x = pos.get_x();
    int y = pos.get_y();
    int z = pos.get_z();

    int cxy, cyz, cxz;

    Sequences *seq = Sequences::getInstance();

    cxy = seq->cost(seq->get_seq(0)[x], seq->get_seq(1)[y]);
    cxz = seq->cost(seq->get_seq(0)[x], seq->get_seq(2)[z]);
    cyz = seq->cost(seq->get_seq(1)[y], seq->get_seq(2)[z]);

    printf("Comparando (%d %d %d) / (%d/%d/%d)\n", x, y, z, cxy, cxz, cyz);

    a.push_back(Node(m_g + 2 * Sequences::GAP,   Coord(x + 1, y,     z    )));
    a.push_back(Node(m_g + 2 * Sequences::GAP,   Coord(x,     y + 1, z    )));
    a.push_back(Node(m_g + 2 * Sequences::GAP,   Coord(x,     y,     z + 1)));
    a.push_back(Node(m_g + cxy + Sequences::GAP, Coord(x + 1, y + 1, z    )));
    a.push_back(Node(m_g + cyz + Sequences::GAP, Coord(x,     y + 1, z + 1)));
    a.push_back(Node(m_g + cxz + Sequences::GAP, Coord(x + 1, y,     z + 1)));
    a.push_back(Node(m_g + cxy + cxz + cyz,      Coord(x + 1, y + 1, z + 1)));
    return a;
}

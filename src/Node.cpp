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
    unsigned int x = pos.get_x();
    unsigned int y = pos.get_y();
    unsigned int z = pos.get_z();

    bool addx, addy, addz;
    int cxy, cyz, cxz;

    Sequences *seq = Sequences::getInstance();

    cxy = seq->cost(seq->get_seq(0)[x], seq->get_seq(1)[y]);
    cxz = seq->cost(seq->get_seq(0)[x], seq->get_seq(2)[z]);
    cyz = seq->cost(seq->get_seq(1)[y], seq->get_seq(2)[z]);

    addx = (x < seq->get_seq(0).length());
    addy = (y < seq->get_seq(1).length());
    addz = (z < seq->get_seq(2).length());

    if (addx)
        a.push_back(Node(m_g + 2 * Sequences::GAP,   Coord(x + 1, y,     z    )));
    if (addy)
        a.push_back(Node(m_g + 2 * Sequences::GAP,   Coord(x,     y + 1, z    )));
    if (addz)
        a.push_back(Node(m_g + 2 * Sequences::GAP,   Coord(x,     y,     z + 1)));
    if (addx && addy)
        a.push_back(Node(m_g + cxy + Sequences::GAP, Coord(x + 1, y + 1, z    )));
    if (addy && addz)
        a.push_back(Node(m_g + cyz + Sequences::GAP, Coord(x,     y + 1, z + 1)));
    if (addx && addz)
        a.push_back(Node(m_g + cxz + Sequences::GAP, Coord(x + 1, y,     z + 1)));
    if (addx && addy && addz)
        a.push_back(Node(m_g + cxy + cxz + cyz,      Coord(x + 1, y + 1, z + 1)));
    return a;
}

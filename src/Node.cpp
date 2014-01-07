/*!
 * \filename Node.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include <algorithm>
#include <iostream>
#include <vector>

#include "Cost.h"
#include "Heuristic.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

/*!
 * Build a node with zero on all atributes
 */
Node::Node()
{
    m_g = 0;
    m_f = 0;
    m_h = 0;
}

/*!
 * Build a node with cost \a g and position \a pos with parent
 * \a parent
 *
 * \warning this constructor use's Heuristics function, so Heuristic::setHeuristic()
 *          MUST be called.
 */
Node::Node(const int g, const Coord& pos, const Coord& parent)
: parent(parent),
  pos(pos)
{
    m_g = g;
    m_h = Heuristic::getHeuristic()->calculate_h(pos);
    m_f = m_g + m_h;
}

/*!
 * Print \a rhs atributes
 */
ostream& operator<<(ostream &lhs, const Node &rhs)
{
    lhs << rhs.pos << "\tg - " << rhs.m_g << " (h - " << rhs.m_h
        << " f - " << rhs.m_f << ")";
    return lhs;
}

/*!
 * Check if coord \a c belongs to the sequences' search space
 */
bool Node::borderCheck(const Coord &c) const
{
    Sequences *seq = Sequences::getInstance();

    for (unsigned int i = 0; i < Sequences::get_seq_num(); i++)
        if ((unsigned int)c[i] > seq->get_seq(i).length())
            return false;
    return true;
}

/*!
 * Return sequence \a i as a bitfield
 */
inline int Node::bitSeq(const int &i) const
{
    return 1 << i;
}

/*!
 * Bit check if the number \a i has sequences \a s1 and \a s2
 */
inline bool Node::bitSeqCheck(const int &i, const int &s1, const int &s2) const
{
    return (i & s1) && (i & s2);
}

/*!
 * Add all neighboors to a vector \a. If it is not a board node,
 * 2pow(n-1) nodes are added.
 */
int Node::getNeigh(vector<Node> &a)
{
    int i;
    Sequences *seq = Sequences::getInstance();
    const int gap_cost = (Sequences::get_seq_num() - 1) * Cost::GAP;
    Coord c;

    /* Vector of tuple. First field cost, Second field, sequence1
       bits, third field, sequence2 bits.
       Example, if sequence 0 and 2 matches, one of the vector fields
       contains first MATCH, second 1, third 4. */
    vector< tuple<int, int, int> > pairwise_costs;

    for (unsigned int i = 0; i < Sequences::get_seq_num() - 1; i++)
    {
        for (unsigned int j = i + 1; j < Sequences::get_seq_num(); j++)
        {
            int cost = Cost::cost(seq->get_seq(i)[pos[i]], seq->get_seq(j)[pos[j]]);
            pairwise_costs.push_back(make_tuple(cost, bitSeq(i), bitSeq(j)));
        }
    }

    int n = bitSeq(Sequences::get_seq_num()) - 1;
    for (i = 1; i < n; i++)
    {
        c = pos.neigh(i);
        if (borderCheck(c))
        {
            int costs = 0; // match and mismatch sum-of-pairs cost
            for (auto it = pairwise_costs.begin() ; it != pairwise_costs.end(); ++it)
                costs += get<0>(*it) * bitSeqCheck(i, get<1>(*it), get<2>(*it));
            a.push_back(Node(m_g + costs + gap_cost, c, pos));
        }
    }
    // add last neighboor without any gap cost
    c = pos.neigh(i);
    if (borderCheck(c))
    {
        int costs = 0;
        for (auto it = pairwise_costs.begin() ; it != pairwise_costs.end(); ++it)
            costs += get<0>(*it);
        a.push_back(Node(m_g + costs, c, pos));
    }
    return 0;
}

/*!
 * Friend function to compare nodes. Highest priority to lower f's.
 */
bool PriorityNode::operator()(Node& n1, Node& n2)
{
    if (n1.m_f > n2.m_f)
        return true;
    return false;
}

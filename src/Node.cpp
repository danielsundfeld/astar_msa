/*!
 * \class Node
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <algorithm>
#include <iostream>
#include <vector>

#include "Cost.h"
#include "Heuristic.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

//! Build a node with zero on all atributes
Node::Node()
{
    m_g = 0;
    m_f = 0;
}

/*!
 * Build a node with cost \a g and position \a pos with parent
 * \a parent
 *
 * \warning this constructor use's Heuristics function, so Heuristic::setHeuristic()
 *          MUST be called.
 */
Node::Node(const int g, const Coord& pos, const int &parenti)
: parenti(parenti),
  pos(pos)
{
    m_g = g;
    m_f = m_g + Heuristic::getHeuristic()->calculate_h(pos);
}

/*!
 * Build a node with maximum values on every camp
 */
Node::Node(const int i)
{
    parenti = i;
    m_g = m_f = std::numeric_limits<int>::max();
    pos = Sequences::get_final_coord();
}

ostream& operator<<(ostream &lhs, const Node &rhs)
{
    lhs << rhs.pos << "\tg - " << rhs.m_g << " (h - " << rhs.get_h()
        << " f - " << rhs.m_f << ")";
    return lhs;
}

bool operator!=(const Node &lhs, const Node &rhs)
{
    if (lhs.m_f != rhs.m_f)
        return true;
    if (lhs.pos != rhs.pos)
        return true;
    return false;
}

//! Check if coord \a c belongs to the sequences' search space
bool Node::borderCheck(const Coord &c) const
{
    for (unsigned int i = 0; i < Sequences::get_seq_num(); i++)
        if (c[i] > Sequences::get_final_coord()[i])
            return false;
    return true;
}

//! Return sequence \a i as a bitfield
inline int Node::bitSeq(const int &i) const
{
    return 1 << i;
}

//! Bit check if the number \a i has sequences \a s1 and \a s2
inline bool Node::bitSeqCheck(const int &i, const int &s1, const int &s2) const
{
    return (i & bitSeq(s1)) && (i & bitSeq(s2));
}

//! Bit check if the number \a i has sequence \a s1
inline bool Node::bitSeqCheck(const int &i, const int &s1) const
{
    return (i & bitSeq(s1));
}

/*!
 * Decide if we have to add a match, mismatch, gap open or gap
 * extension cost to this pair.
 * Example: consider the following aligment:
 * AAA
 * A--
 * A--
 *
 * In graph, it is represented by the path:
 * (0, 0, 0)
 * (1, 1, 1)
 * (2, 1, 1)
 * (3, 1, 1)
 *
 * From node (0, 0, 0) to (1, 1, 1):
 * The test bitSeqCheck is always true, so we return mm_cost 3 times
 *
 * From node (1, 1, 1) to (2, 1, 1) with s1 = 0 s2 = 1:
 * The test bitSeqCheck is false.
 * The test bitSeqCheck with "s1" is true, so we must look at s2:
 * s2 is 1. (1, 1, 1) parent is (0, 0, 0). son[1] = 1 parent[1] = 0
 * It is an open gap.
 * From node (1, 1, 1) to (2, 1, 1) with s1 = 0 s2 = 2, same behavior
 * From node (1, 1, 1) to (2, 1, 1) with s1 = 1 s2 = 2:
 * none bitSeqCheck test is true. return 0 (gap/gap cost)
 *
 * From node (2, 1, 1) to (3, 1, 1) with s1 = 0 s2 = 1:
 * Almost same as before, bitSeqCheck with "s1" is true
 * s2 is 1. (2, 1, 1) parent is (1, 1, 1). son[1] = 1 parent[1] = 1
 * It is an extension gap.
 */
inline int Node::pairCost(const int &neigh_num, const int &mm_cost, const int &s1, const int &s2) const
{
    int s; // Sequence to check if is open or extended gap

    if (bitSeqCheck(neigh_num, s1, s2))
        return mm_cost;

    if (bitSeqCheck(neigh_num, s1))
        s = s2;
    else if (bitSeqCheck(neigh_num, s2))
        s = s1;
    else
        return Cost::GapGap;

   /* The following code is equivalent to, but much quicker then:
    Coord parent = pos.parent(parenti);
    if (son[s] != parent[s]) */

    // Compare a node with his grandparent to decide gap penalty.
    if (bitSeqCheck(parenti, s) != bitSeqCheck(neigh_num, s))
        return Cost::GapOpen;
    return Cost::GapExtension;
}

/*!
 * Add all neighboors to a vector \a a. If it is not a board node,
 * 2pow(n-1) nodes are added.
 */
int Node::getNeigh(vector<Node> a[], int vec_size)
{
    int i;
    Sequences *seq = Sequences::getInstance();
    Coord c;

    /* Vector of tuple. First field cost, Second field, sequence1.
       third field, sequence2.
       Example, if sequence 0 and 2 matches, one of the vector fields
       contains first MATCH, second 0, third 2. */
    vector< tuple<int, int, int> > pairwise_costs;

    for (unsigned int i = 0; i < Sequences::get_seq_num() - 1; i++)
    {
        for (unsigned int j = i + 1; j < Sequences::get_seq_num(); j++)
        {
            int cost = Cost::cost(seq->get_seq(i)[pos[i]], seq->get_seq(j)[pos[j]]);
            pairwise_costs.push_back(make_tuple(cost, i, j));
        }
    }

    int n = bitSeq(Sequences::get_seq_num()) - 1;
    for (i = 1; i <= n; i++)
    {
        c = pos.neigh(i);
        if (borderCheck(c))
        {
            int costs = 0; // match, mismatch and gap sum-of-pairs cost

            for (auto it = pairwise_costs.begin() ; it != pairwise_costs.end(); ++it)
                costs += pairCost(i, get<0>(*it), get<1>(*it), get<2>(*it));
            a[c.get_id(vec_size)].push_back(Node(m_g + costs, c, i));
        }
    }
    return 0;
}

#ifdef NO_LIB_BOOST
//! Friend function to compare nodes. Highest priority to lower f's.
bool PriorityNode::operator()(Node& n1, Node& n2)
{
    if (n1.m_f > n2.m_f)
        return true;
    return false;
}
#endif

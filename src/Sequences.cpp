/*!
 * \class Sequences
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Sequences.h"

#include <iostream>
#include <string>

#include "Coord.h"
#include "Node.h"

Sequences::Sequences()
{
    n_seq = 0;
}

//! Number of sequences
int Sequences::n_seq = 0;
//! Singleton instance
Sequences Sequences::instance;
//! Destination coord
int Sequences::final_coord[MaxSequences] = {};

//! Destroy the instance
void Sequences::destroyInstance()
{
    n_seq = 0;

    for (int i = 0; i < MaxSequences; ++i)
        final_coord[i] = 0;
}

//! Save the string \a x as an Sequence
int Sequences::set_seq(const std::string &x)
{
    seqs.push_back(x);
    final_coord[n_seq] = x.length();
    ++n_seq;
    return n_seq;
}

template <int N>
Coord<N> Sequences::get_final_coord()
{
    Coord<N> c;
    for (int i = 0; i < N; ++i)
        c[i] = final_coord[i];
    return c;
}

template <int N>
Coord<N> Sequences::get_initial_coord()
{
    Coord<N> c;
    return c;
}

//! Create a initial node of the alignment
template <int N>
Node<N> Sequences::get_initial_node()
{
    /* The "father" field must point to a negative coord, so the
       affine gaps are calculated correctly.  */
    int coord_negative = (1 << N) - 1;
    return Node<N>(0, Sequences::get_initial_coord<N>(), coord_negative);
}

//! Check if \a c is the destination
template <int N>
bool Sequences::is_final(const Coord<N> &c)
{
    for (int i = 0; i < N; ++i)
        if (c[i] != final_coord[i])
            return false;
    return true;
}

#define DECLARE_SEQUENCE_TEMPLATE( X ) \
template class Coord< X > Sequences::get_final_coord< X >(); \

#define DECLARE_INITIAL_COORD_TEMPLATE( X ) \
template class Coord< X > Sequences::get_initial_coord< X >(); \

#define DECLARE_IS_FINAL_TEMPLATE( X ) \
template bool Sequences::is_final(const Coord < X > &c); \

#define DECLARE_INITIAL_NODE_TEMPLATE( X ) \
template class Node< X > Sequences::get_initial_node< X >(); \

MAX_NUM_SEQ_HELPER(DECLARE_SEQUENCE_TEMPLATE);
MAX_NUM_SEQ_HELPER(DECLARE_INITIAL_COORD_TEMPLATE);
MAX_NUM_SEQ_HELPER(DECLARE_IS_FINAL_TEMPLATE);
MAX_NUM_SEQ_HELPER(DECLARE_INITIAL_NODE_TEMPLATE);

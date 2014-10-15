/*!
 * \class Coord
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <iostream>

#include "Coord.h"

//! Construct a Coord<N> with N dimensions initialized as 'init'
template < int N >
Coord<N>::Coord(const int init)
{
    for (int i = 0; i < N; ++i)
        m_coord[i] = init;
}

template < int N >
Coord<N>& Coord<N>::operator=(const Coord<N> &rhs)
{
    if (this == &rhs) // identify self-assignment
        return *this; // do nothing
    for (int i = 0; i < N; ++i)
        m_coord[i] = rhs.m_coord[i];
    return *this;
}


template < int N >
std::ostream& operator<<(std::ostream &lhs, const Coord<N> &rhs)
{
    if (N == 0)
        return lhs;

    lhs << "(" << rhs.m_coord[0];
    for (int i = 1; i < N; ++i)
        lhs << " " << rhs.m_coord[i];
    lhs << ")";
    return lhs;
}

template < int N >
bool Coord<N>::operator!=(const Coord<N> &rhs) const
{
    for (int i = 0; i < N; ++i)
        if (m_coord[i] != rhs.m_coord[i])
            return true;
    return false;
}

template < int N >
bool Coord<N>::operator==(const Coord<N> &rhs) const
{
    return !(*this != rhs);
}

template < int N >
bool Coord<N>::operator<(const Coord<N> &rhs) const
{
    for (int i = 0; i < N; ++i)
    {
        if (m_coord[i] > rhs.m_coord[i])
            return false;
        if (m_coord[i] < rhs.m_coord[i])
            return true;
    }
    return false;
}

//! Return the value on the \a n - dimension
template < int N >
const uint16_t& Coord<N>::operator[](const uint16_t n) const
{
    return m_coord[n];
}

//! Return the value on the \a n - dimension
template < int N >
uint16_t& Coord<N>::operator[](const uint16_t n)
{
    return m_coord[n];
}

/*!
 * Helper function to produce a neighboor.
 * If a 3 dimensions coord(x, y, z) call neigh(1) it produces
 * coord(x + 1, y, z), neigh(7) produces coord(x + 1, y + 1, z +1)
 */
template < int N >
Coord<N> Coord<N>::neigh(int n) const
{
    int i = 0;

    Coord<N> c(*this);
    while (n)
    {
        if (n & 1)
            c[i] += 1;
        n = n >> 1;
        i++;
    }
    return c;
}

/*!
 * Inverse of Coord:neigh(int n)
 * neigh is a highly called function I dont care about duplicate code
 */
template < int N >
Coord<N> Coord<N>::parent(int n) const
{
    int i = 0;

    Coord<N> c(*this);
    while (n)
    {
        if (n & 1)
            c[i] -= 1;
        n = n >> 1;
        i++;
    }
    return c;
}

// This file have a friend function that also need to be templated to max seq
#define COORD_DECLARE_FRIEND( X ) \
template std::ostream& operator<< < X >(std::ostream&, Coord< X > const&); \

MAX_NUM_SEQ_HELPER(COORD_DECLARE_FRIEND);
MAX_NUM_SEQ_HELPER(COORD_DECLARE_COORD_TEMPLATE);

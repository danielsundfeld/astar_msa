/*!
 * \filename Coord.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include <iostream>
#include <vector>

#include "Coord.h"

using namespace std;

Coord::Coord()
{
}

//! Construct a Coord with \a d dimensions initialized as 'init'
Coord::Coord(const int d, const int init)
{
    m_coord = vector<int>(d, init);
}

//! Construct a 3-dimensions coord
Coord::Coord(const int x, const int y, const int z)
{
    m_coord.push_back(x);
    m_coord.push_back(y);
    m_coord.push_back(z);
}

Coord& Coord::operator=(const Coord &rhs)
{
    if (this == &rhs) // identify self-assignment
        return *this; // do nothing
    m_coord = rhs.m_coord;
    return *this;
}

bool Coord::operator!=(const Coord &rhs) const
{
    return (m_coord != rhs.m_coord);
}

bool Coord::operator==(const Coord &rhs) const
{
    return (m_coord == rhs.m_coord);
}

bool Coord::operator<(const Coord &rhs) const
{
    return (m_coord < rhs.m_coord);
}

ostream& operator<<(ostream &lhs, const Coord &rhs)
{
    auto it = rhs.m_coord.cbegin();

    if (it == rhs.m_coord.cend())
        return lhs;
    lhs << "(" << *it;
    ++it;

    for (; it != rhs.m_coord.cend(); ++it)
        lhs << " " << *it;

    lhs << ")";
    return lhs;
}

//! Return the value on the \a n - dimension
const int& Coord::operator[](const int n) const
{
    return m_coord[n];
}

//! Return the value on the \a n - dimension
int& Coord::operator[](const int n)
{
    return m_coord[n];
}

/*!
 * Increases de dimension of the current coord, ading \a n as the
 * last dimension
 */
void Coord::append(const int &n)
{
    m_coord.push_back(n);
}

/*!
 * Helper function to produce a neighboor.
 * If a 3 dimensions coord(x, y, z) call neigh(1) it produces
 * coord(x + 1, y, z), neigh(7) produces coord(x + 1, y + 1, z +1)
 */
Coord Coord::neigh(int n) const
{
    int i = 0;

    Coord c = *this;
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
Coord Coord::parent(int n) const
{
    int i = 0;

    Coord c = *this;
    while (n)
    {
        if (n & 1)
            c[i] -= 1;
        n = n >> 1;
        i++;
    }
    return c;
}

//!< Removes all elements from Coord
void Coord::clear()
{
    m_coord.clear();
}

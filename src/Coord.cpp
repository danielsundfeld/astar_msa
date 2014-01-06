#include <iostream>
#include <vector>

#include "Coord.h"

using namespace std;

Coord::Coord()
{
}

/*!
 * Construct a Coord with \a d dimensions initialized as '0'.
 */
Coord::Coord(int d)
{
    m_coord = vector<int>(d, 0);
}

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

const int& Coord::operator[](const int n) const
{
    return m_coord[n];
}

int& Coord::operator[](const int n)
{
    return m_coord[n];
}

void Coord::append(const int &n)
{
    m_coord.push_back(n);
}

/*!
 * Helper function to produce all neighboors.
 * If a 3 dimensions coord(x, y, z) call neigh(1) it produces
 * coord(x + 1, y, z), neigh(7) produces coord(x + 1, y + 1, z +1)
 * and so on.
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

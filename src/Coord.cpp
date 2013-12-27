#include <iostream>
#include <vector>

#include "Coord.h"

using namespace std;

Coord::Coord()
{
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

int& Coord::operator[](const int n)
{
    return m_coord[n];
}

void Coord::append(const int &n)
{
    m_coord.push_back(n);
}

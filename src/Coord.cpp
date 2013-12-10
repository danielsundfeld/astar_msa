#include <iostream>
#include <vector>

#include "Coord.h"

using namespace std;

Coord::Coord()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Coord::Coord(const int x, const int y, const int z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

Coord& Coord::operator=(const Coord &rhs)
{
    if (this == &rhs) // identify self-assignment
        return *this; // do nothing
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;

    return *this;
}

bool Coord::operator==(const Coord &rhs) const
{
    if (m_x != rhs.m_x)
        return false;
    if (m_y != rhs.m_y)
        return false;
    if (m_z != rhs.m_z)
        return false;
    return true;
}

bool Coord::operator<(const Coord &rhs) const
{
    if (m_x == rhs.m_x && m_y == rhs.m_y && m_z < rhs.m_z)
        return true;
    if (m_x == rhs.m_x && m_y < rhs.m_y)
        return true;
    if (m_x < rhs.m_x)
        return true;
    return false;
}

ostream& operator<<(ostream &lhs, const Coord &rhs)
{
    lhs << "(" << rhs.m_x << " " << rhs.m_y << " " << rhs.m_z << ")";
    return lhs;
}

//TODO operator -

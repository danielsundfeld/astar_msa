#include <vector>
#include "Coord.h"

using namespace std;

Coord::Coord()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Coord::Coord(int x, int y, int z)
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

int Coord::operator==(const Coord &rhs) const
{
    if (m_x != rhs.m_x)
        return 0;
    if (m_y != rhs.m_y)
        return 0;
    if (m_z != rhs.m_z)
        return 0;
    return 1;
}

int Coord::operator<(const Coord &rhs) const
{
    if (m_x == rhs.m_x && m_y == rhs.m_y && m_z < rhs.m_z)
        return 1;
    if (m_x == rhs.m_x && m_y < rhs.m_y)
        return 1;
    if (m_x < rhs.m_x)
        return 1;
    return 0;
}


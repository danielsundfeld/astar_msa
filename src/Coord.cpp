#include "Coord.h"

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

    return *this;
}

int Coord::operator==(const Coord &rhs) const
{
    if (this->m_x != rhs.m_x)
        return 0;
    if (this->m_y != rhs.m_y)
        return 0;
    if (this->m_z != rhs.m_z)
        return 0;
    return 1;
}

int Coord::operator<(const Coord &rhs) const
{
    if (this->m_x == rhs.m_x && this->m_y == rhs.m_y && this->m_z < rhs.m_z)
        return 1;
    if (this->m_x == rhs.m_x && this->m_y < rhs.m_y)
        return 1;
    if (this->m_x < rhs.m_x)
        return 1;
    return 0;
}


/*!
 * \class CoordHash
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Coord.h"

int CoordHash::get_id(const Coord &c, const int size)
{
    return (c.get_sum() >> HASH_SHIFT) % size;
}

/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * This file implements the Hash Functions to class Coord
 */
#include "Coord.h"

//! Return the sum of elements
int Coord::get_sum() const
{
    int sum = 0;
    for (auto it = m_coord.cbegin(); it != m_coord.cend(); ++it)
        sum += *it;
    return sum;
}

//! Return the full-sum-hash
int Coord::full_sum_hash(const int size) const
{
    return (get_sum() >> HASH_SHIFT) % size;
}

//! Main CoordHash function: return the hash to the space \a size
int Coord::get_id(const int size) const
{
    return full_sum_hash(size);
}

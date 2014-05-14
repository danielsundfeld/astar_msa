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

//! z_order_curve hash on multidimension coordinates
unsigned int Coord::z_order_curve_hash() const
{
    int hash = 0;
    int bit_to_read = 0;

    for (unsigned int bit_to_write = 1; bit_to_write != 0; )
    {
        for (unsigned int j = 0; j < m_coord.size() && bit_to_write != 0; ++j)
        {
            if (m_coord[j] & (1 << bit_to_read))
                hash |= bit_to_write;
            bit_to_write <<= 1;
        }
        ++bit_to_read;
    }
    return hash;
}

//! Main CoordHash function: return the hash to the space \a size
int Coord::get_id(const int size) const
{
    return full_sum_hash(size);
}

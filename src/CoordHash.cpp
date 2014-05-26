/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * This file implements the Hash Functions to class Coord
 */
#include "Coord.h"

//! Return the sum of elements
unsigned int Coord::get_sum() const
{
    int sum = 0;
    for (auto it = m_coord.cbegin(); it != m_coord.cend(); ++it)
        sum += *it;
    return sum;
}

//! Return the full-sum-hash
unsigned int Coord::sum_hash(const int size) const
{
    return (get_sum() >> HASH_SHIFT) % size;
}

//! Return the sum of first and second elements
unsigned int Coord::get_part_sum() const
{
    return m_coord[0] + m_coord[1];
}

//! Return the part-sum-hash
unsigned int Coord::part_sum_hash(const int size) const
{
    return (get_part_sum() >> HASH_SHIFT) % size;
}

//! z_order_curve on multidimension coordinates
unsigned int Coord::get_z_order_curve() const
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

/*!
 * Return the full z-order-hash
 * \deprecated See Coord::z_order_hash
 */
unsigned int Coord::z_order_hash_slow(const int size) const
{
    return (get_z_order_curve() >> HASH_SHIFT) % size;
}

/*!
 * Return the full z-order-hash fast. A full z-order-curve calculus
 * includes all bits. We want to use this as a hash (check the
 * Coord::z_order_hash_slow() function to see the idea), but not all
 * bits must be calculated. The shift operation discards the less
 * significant bits, and the mod operation discards the higher
 * significant bits. This function do not calculate these bits,
 * instead of discarding them, producing the same result with less
 * operations. Wow. Much faster. Such speed. Very intelligent.
 */
unsigned int Coord::z_order_hash(const int size) const
{
    int hash = 0;
    // Shift operation, start reading
    int bit_to_read = HASH_SHIFT / m_coord.size();

    // MOD operation, stop writing after total_bits
    unsigned int total = 1 << (size);

    for (unsigned int bit_to_write = 1; bit_to_write <= total; )
    {
        for (unsigned int j = 0; j < m_coord.size() && bit_to_write <= total; ++j)
        {
            if (m_coord[j] & (1 << bit_to_read))
                hash |= bit_to_write;
            bit_to_write <<= 1;
        }
        ++bit_to_read;
    }
    /* HASH_SHIFT 1 means: discard the first bit from the first sequence, but
    use the first bit of the other sequences. */
    //TODO: optimize this MOD size operation
    return (hash >> (HASH_SHIFT % m_coord.size())) % size;
}

//! Main CoordHash function: return the hash to the space \a size
unsigned int Coord::get_id(const int size) const
{
#ifdef HASHFZORDER
    return z_order_hash(size);
#elif HASHPSUM
    return part_sum_hash(size);
#else
    return sum_hash(size);
#endif
}

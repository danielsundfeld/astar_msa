/*!
 * \class Coord
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * This file implements the Hash Functions to class Coord
 */
#include <cmath>
#include <limits>

#include "Coord.h"

#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")

//! Return the sum of elements
template < int N >
unsigned int Coord<N>::get_sum() const
{
    int sum = 0;
    for (int i = 0; i < N; ++i)
        sum += m_coord[i];
    return sum;
}

//! Return the full-sum-hash
template < int N >
unsigned int Coord<N>::sum_hash(const int size) const
{
    return (get_sum() >> HASH_SHIFT) % size;
}

//! Return the sum of first and second elements
template < int N >
unsigned int Coord<N>::get_part_sum() const
{
    return m_coord[0] + m_coord[1];
}

//! Return the part-sum-hash
template < int N >
unsigned int Coord<N>::part_sum_hash(const int size) const
{
    return (get_part_sum() >> HASH_SHIFT) % size;
}

//! z_order_curve on multidimension coordinates
template < int N >
unsigned int Coord<N>::get_z_order_curve() const
{
    int hash = 0;
    int bit_to_read = 0;

    for (unsigned int bit_to_write = 1; bit_to_write != 0; )
    {
        for (unsigned int j = 0; j < N && bit_to_write != 0; ++j)
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
 * \deprecated See Coord<N>::z_order_hash
 */
template < int N >
unsigned int Coord<N>::z_order_hash_slow(const int size) const
{
    return (get_z_order_curve() >> HASH_SHIFT) % size;
}

/*!
 * Return the full z-order-hash fast. A full z-order-curve calculus
 * includes all bits. We want to use this as a hash (check the
 * Coord<N>::z_order_hash_slow() function to see the idea), but not all
 * bits must be calculated. The shift operation discards the less
 * significant bits, and the mod operation discards the higher
 * significant bits. This function do not calculate these bits,
 * instead of discarding them, producing the same result with less
 * operations. Wow. Much faster. Such speed. Very intelligent.
 */
template < int N >
unsigned int Coord<N>::z_order_hash(const int size) const
{
    int hash = 0;
    // Shift operation, start reading
    int bit_to_read = HASH_SHIFT / N;

    // MOD operation, stop writing after bits
    unsigned int bits = log2(size) + (HASH_SHIFT % N) + 1;
    unsigned int total = 1 << bits;
    if (total == 0)
        total = std::numeric_limits<unsigned int>::max();

    for (unsigned int bit_to_write = 1; bit_to_write <= total; )
    {
        for (unsigned int j = 0; j < N && bit_to_write <= total; ++j)
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
    return (hash >> (HASH_SHIFT % N)) % size;
}

//! Same Coord<N>::z_order_hash usage
template < int N >
unsigned int Coord<N>::part_z_order_hash(const int size) const
{
    int hash = 0;
    // Shift operation, start reading
    int bit_to_read = HASH_SHIFT / 2;

    // MOD operation, stop writing after bits
    unsigned int bits = log2(size) + (HASH_SHIFT % 2) + 1;
    unsigned int total = 1 << bits;
    if (total == 0)
        total = std::numeric_limits<unsigned int>::max();

    for (unsigned int bit_to_write = 1; bit_to_write <= total; )
    {
        for (unsigned int j = 0; j < 2 && bit_to_write <= total; ++j)
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
    return (hash >> (HASH_SHIFT % 2)) % size;
}

//! Main CoordHash function: return the hash to the space \a size
template < int N >
unsigned int Coord<N>::get_id(const int size) const
{
#ifdef HASHFSUM
    return sum_hash(size);
#elif HASHPSUM
    return part_sum_hash(size);
#elif HASHPZORDER
    return part_z_order_hash(size);
#else
    #ifndef HASHFZORDER
        #warning HASH NOT DEFINED, USING FULL-ZORDER
    #endif
    return z_order_hash(size);
#endif
}

MAX_NUM_SEQ_TEMPLATE_HELPER(COORD_DECLARE_COORD_TEMPLATE);

#pragma GCC pop_options

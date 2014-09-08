/*!
 * \class Coord
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * This file implements the Hash Functions to class Coord
 */
#include <cmath>
#include <stdexcept>
#include <limits>

#include "Coord.h"

using namespace std;

int hash_shift = HASH_SHIFT;
hashType hash_type = HashFZorder;
const char* const hash_name_pretty[] = {
    "Full-Zorder",
    "Partial-Zorder",
    "Full-Sum",
    "Partial-Sum",
};

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
template < int Shift >
unsigned int Coord<N>::sum_hash(const int size) const
{
    return (get_sum() >> Shift) % size;
}

//! Return the sum of first and second elements
template < int N >
unsigned int Coord<N>::get_part_sum() const
{
    return m_coord[0] + m_coord[1];
}

//! Return the part-sum-hash
template < int N >
template < int Shift >
unsigned int Coord<N>::part_sum_hash(const int size) const
{
    return (get_part_sum() >> Shift) % size;
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
template < int Shift >
unsigned int Coord<N>::z_order_hash_slow(const int size) const
{
    return (get_z_order_curve() >> Shift) % size;
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
template < int Shift >
unsigned int Coord<N>::z_order_hash(const int size) const
{
    int hash = 0;
    // Shift operation, start reading
    int bit_to_read = Shift / N;

    // MOD operation, stop writing after bits
    unsigned int bits = log2(size) + (Shift % N) + 1;
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
    /* Shift 1 means: discard the first bit from the first sequence, but
    use the first bit of the other sequences. */
    //TODO: optimize this MOD size operation
    return (hash >> (Shift % N)) % size;
}

//! Same Coord<N>::z_order_hash usage
template < int N >
template < int Shift >
unsigned int Coord<N>::part_z_order_hash(const int size) const
{
    int hash = 0;
    // Shift operation, start reading
    int bit_to_read = Shift / 2;

    // MOD operation, stop writing after bits
    unsigned int bits = log2(size) + (Shift % 2) + 1;
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
    /* Shift 1 means: discard the first bit from the first sequence, but
       use the first bit of the other sequences. */
    //TODO: optimize this MOD size operation
    return (hash >> (Shift % 2)) % size;
}

//! Decide with shift call, based on the configured hash_type
template < int N >
template < int Shift >
unsigned int Coord<N>::get_id_shifted(const int size) const
{
    switch (hash_type)
    {
        case HashFSum:
            return sum_hash<Shift>(size);
        case HashPSum:
            return part_sum_hash<Shift>(size);
        case HashPZorder:
            return part_z_order_hash<Shift>(size);
        case HashFZorder:
        default:
            return z_order_hash<Shift>(size);
    }
}

//! Main CoordHash function: return the hash to the space \a size
template < int N >
unsigned int Coord<N>::get_id(const int size) const
{
    switch (hash_shift)
    {
        case 0:
            return get_id_shifted<0>(size);
        case 1:
            return get_id_shifted<1>(size);
        case 2:
            return get_id_shifted<2>(size);
        case 3:
            return get_id_shifted<3>(size);
        case 4:
            return get_id_shifted<4>(size);
        case 5:
            return get_id_shifted<5>(size);
        case 6:
            return get_id_shifted<6>(size);
        case 7:
            return get_id_shifted<7>(size);
        case 8:
            return get_id_shifted<8>(size);
        case 9:
            return get_id_shifted<9>(size);
        case 10:
            return get_id_shifted<10>(size);
        case 11:
            return get_id_shifted<11>(size);
        case 12:
            return get_id_shifted<12>(size);
        case 13:
            return get_id_shifted<13>(size);
        case 14:
            return get_id_shifted<14>(size);
        case 15:
            return get_id_shifted<15>(size);
        case 16:
            return get_id_shifted<16>(size);
        case 17:
            return get_id_shifted<17>(size);
        case 18:
            return get_id_shifted<18>(size);
        case 19:
            return get_id_shifted<19>(size);
        case 20:
            return get_id_shifted<20>(size);
        case 21:
            return get_id_shifted<21>(size);
        default:
            throw std::invalid_argument("Invalid Hash Shift");
            return get_id_shifted<1>(size);
    }
    return -1;
}

template < int N >
const char* Coord<N>::get_hash_name()
{
    return hash_name_pretty[hash_type];
}

template < int N >
int Coord<N>::get_hash_shift()
{
    return hash_shift;
}

//! Configure \a shift and \a type as hash parameter
void Coord_configure_hash(hashType type, int shift)
{
    hash_type = type;
    hash_shift = shift;
}

MAX_NUM_SEQ_TEMPLATE_HELPER(COORD_DECLARE_COORD_TEMPLATE);

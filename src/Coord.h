/*!
 * \class Coord
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief A multidimensional coordinate with fixed size
 */
#ifndef _COORD_H
#define _COORD_H
#include <iostream>
#include <vector>

#include "CoordHash.h"
#include "max_seq_template_helper.h"

template < int N > class Coord;
template < int N > std::ostream& operator<< (std::ostream &lhs, const Coord<N> &rhs);

template < int N >
class Coord {
    private:
        uint16_t m_coord[N];
        template <int Shift> unsigned int get_id_shifted(const int size) const;

    public:
        Coord(const int init = 0);
        Coord<N>& operator=(const Coord<N> &rhs);
        friend std::ostream &operator<< <>(std::ostream &lhs, const Coord<N> &rhs);
        bool operator!=(const Coord &rhs) const;
        bool operator==(const Coord &rhs) const;
        bool operator<(const Coord &rhs) const;
        const uint16_t& operator[](const uint16_t n) const;
        uint16_t& operator[](const uint16_t n);

        Coord neigh(int n) const;
        Coord parent(int n) const;

        // CoordHash functions helpers
        unsigned int get_sum() const;
        unsigned int get_part_sum() const;
        unsigned int get_z_order_curve() const;

        // CoordHash hash functions
        template <int Shift> unsigned int sum_hash(const int size) const;
        template <int Shift> unsigned int part_sum_hash(const int size) const;
        template <int Shift> unsigned int z_order_hash_slow(const int size) const;
        template <int Shift> unsigned int z_order_hash(const int size) const;
        template <int Shift> unsigned int part_z_order_hash(const int size) const;

        // CoordHash main function
        unsigned int get_id(const int size) const;
};

// Coord implementation files must call this
#define COORD_DECLARE_COORD_TEMPLATE( X ) \
template class Coord< X >; \
// Add other defines on cpp files only, not here
#endif

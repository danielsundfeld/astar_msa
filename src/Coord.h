/*!
 * \class Coord
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief A multidimensional coordinate
 */
#ifndef _COORDS_H
#define _COORDS_H
#include <iostream>
#include <vector>

#include "CoordHash.h"

using namespace std;

class Coord {
    private:
        vector<int> m_coord;

    public:
        Coord();
        Coord(const int d, const int init = 0);
        Coord(const int x, const int y, const int z);
        Coord &operator=(const Coord &rhs);
        bool operator!=(const Coord &rhs) const;
        bool operator==(const Coord &rhs) const;
        bool operator<(const Coord &rhs) const;
        friend ostream &operator<<(ostream &lhs, const Coord &rhs);
        const int& operator[](const int n) const;
        int& operator[](const int n);
        void append(const int &n);
        Coord neigh(int n) const;
        Coord parent(int n) const;
        void clear();

        // CoordHash functions helpers
        unsigned int get_sum() const;
        unsigned int get_z_order_curve() const;

        // CoordHash hash functions
        unsigned int sum_hash(const int size) const;
        unsigned int z_order_hash(const int size) const;

        // CoordHash main function
        unsigned int get_id(const int size) const;
};

#endif

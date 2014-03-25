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

using namespace std;

class Coord {
    private:
        int m_sum;
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
        int get_sum() { return m_sum; };
};

#endif

#ifndef _COORDS_H
#define _COORDS_H
#include <iostream>
#include <vector>

using namespace std;

class Coord {
    private:
        int m_x, m_y, m_z;

    public:
        Coord();
        Coord(int x, int y, int z);
        Coord &operator=(const Coord &rhs);
        int operator==(const Coord &rhs) const;
        int operator<(const Coord &rhs) const;
        friend ostream &operator<<(ostream &lhs, const Coord &rhs);
        int get_x() { return m_x; };
        int get_y() { return m_y; };
        int get_z() { return m_z; };
};

#endif

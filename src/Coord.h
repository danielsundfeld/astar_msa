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
        Coord(const int x, const int y, const int z);
        Coord &operator=(const Coord &rhs);
        bool operator!=(const Coord &rhs) const;
        bool operator==(const Coord &rhs) const;
        bool operator<(const Coord &rhs) const;
        friend ostream &operator<<(ostream &lhs, const Coord &rhs);
        int get_x() const { return m_x; };
        int get_y() const { return m_y; };
        int get_z() const { return m_z; };
};

#endif

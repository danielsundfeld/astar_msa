#ifndef _COORDS_H
#define _COORDS_H
#include <iostream>
#include <vector>

using namespace std;

class Coord {
    private:
        vector<int> m_coord;

    public:
        Coord();
        Coord(const int x, const int y, const int z);
        Coord &operator=(const Coord &rhs);
        bool operator!=(const Coord &rhs) const;
        bool operator==(const Coord &rhs) const;
        bool operator<(const Coord &rhs) const;
        friend ostream &operator<<(ostream &lhs, const Coord &rhs);
        int& operator[](const int n);
        void append(const int &n);
        int get_x() const { return m_coord[0]; };
        int get_y() const { return m_coord[1]; };
        int get_z() const { return m_coord[2]; };
};

#endif

/*!
 * \class CoordHash
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Hash functions on multidimensional coordinates
 */
#ifndef _COORD_HASH_H
#define _COORD_HASH_H

/*! The size of the shift on the get_id() function */
#ifndef HASH_SHIFT
    #define HASH_SHIFT  5
#endif

class Coord;

class CoordHash {
    private:
        CoordHash();

    public:
        static int get_id(const Coord &c, const int size);
};

#endif

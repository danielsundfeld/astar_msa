#ifndef _HEURISTC_H
#define _HEURISTC_H
#include "Coord.h"

class Heuristic {
    public:
        virtual int calculate_heuristic(const Coord &c) const = 0;
};
#endif

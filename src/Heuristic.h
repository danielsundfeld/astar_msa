#ifndef _HEURISTC_H
#define _HEURISTC_H
#include "Coord.h"

class Heuristic {
    private:
        static Heuristic *instance;

    public:
        virtual ~Heuristic();
        static Heuristic* getHeuristic();
        static void setHeuristic(Heuristic *p);

        virtual int calculate_h(const Coord &c) const = 0;
};
#endif

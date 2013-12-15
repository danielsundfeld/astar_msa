#ifndef _HEURISTC_ALL_P2_H
#define _HEURISTC_ALL_P2_H
#include "Coord.h"
#include "Heuristic.h"

class HeuristicAllP2 : public Heuristic
{
    public:
        HeuristicAllP2();
        ~HeuristicAllP2();

        void init();
        int calculate_heuristic(const Coord &c) const;
        static int calculate_h(const Coord &c);
};
#endif

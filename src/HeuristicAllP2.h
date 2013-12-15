#ifndef _HEURISTC_ALL_P2_H
#define _HEURISTC_ALL_P2_H
#include "Coord.h"
#include "Heuristic.h"
#include "Sequences.h"

class HeuristicAllP2 : public Heuristic
{
    private:
        static HeuristicAllP2 *instance;
        HeuristicAllP2();
        ~HeuristicAllP2();
        Sequences *m_seq;

    public:
        static HeuristicAllP2* getInstance();
        static void destroyInstance();

        void init();
        int calculate_h(const Coord &c) const;
};
#endif

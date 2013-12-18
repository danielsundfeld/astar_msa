#ifndef _HEURISTC_ALL_P2_H
#define _HEURISTC_ALL_P2_H
#include <map>

using namespace std;

#include "Coord.h"
#include "Heuristic.h"
#include "PairAlign.h"
#include "Sequences.h"

class HeuristicHPair : public Heuristic
{
    private:
        static HeuristicHPair *instance;
        HeuristicHPair();
        ~HeuristicHPair();
        Sequences *m_seq;
        vector<PairAlign*> mAligns;

    public:
        static HeuristicHPair* getInstance();
        static void destroyInstance();

        void init();
        int calculate_h(const Coord &c) const;
};
#endif

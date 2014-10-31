/*!
 * \class HeuristicHPair
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Heuristic using all pairwise scores
 */
#ifndef _HEURISTICHPAIR_H
#define _HEURISTICHPAIR_H

#include "Coord.h"
#include "PairAlign.h"
#include "Sequences.h"

class HeuristicHPair
{
    public:
        static HeuristicHPair* getInstance();
        static void destroyInstance();
        static HeuristicHPair* getHeuristic();
        static void setHeuristic(HeuristicHPair *p);

        void init();
        template <int N> int calculate_h(const Coord<N> &c) const;

    private:
        static HeuristicHPair *instance;
        HeuristicHPair();
        ~HeuristicHPair();
        std::vector<PairAlign*> mAligns;
};
#endif

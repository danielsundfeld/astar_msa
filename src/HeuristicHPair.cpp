/*!
 * \class HeuristicHPair
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <iostream>

#include "Coord.h"
#include "HeuristicHPair.h"
#include "PairAlign.h"
#include "Sequences.h"
#include "TimeCounter.h"

//! Singleton instance
HeuristicHPair* HeuristicHPair::instance = NULL;

HeuristicHPair::HeuristicHPair()
{
    mAligns.clear();
}

//! Free all pairwise alignments
HeuristicHPair::~HeuristicHPair()
{
    for (std::vector<PairAlign*>::iterator it = mAligns.begin() ; it != mAligns.end(); ++it)
        delete *it;
}

//! Return the current instance. Creates, if needed
HeuristicHPair* HeuristicHPair::getInstance()
{
    if (!instance)
        instance = new HeuristicHPair();
    return instance;
}

//! Free's the memory, destroying the instance
void HeuristicHPair::destroyInstance()
{
    delete instance;
    instance = NULL;
}

//! Return the current heuristic
HeuristicHPair* HeuristicHPair::getHeuristic()
{
    return instance;
}

//! Set the current heuristic as \a p
void HeuristicHPair::setHeuristic(HeuristicHPair *p)
{
    instance = p;
}

/*!
 * Call this function, after all Sequences are loaded.
 * Do the pairwise alignment of all Sequences and set HeuristicHPair
 * as the a-star Heuristic
 */
void HeuristicHPair::init()
{
    TimeCounter tp("Phase 1 - init heuristic: ");
    Sequences *seq = Sequences::getInstance();
    int seq_num = Sequences::get_seq_num();
    setHeuristic(instance);

    std::cout << "Starting pairwise alignments... " << std::flush;
    for (int i = 0; i < seq_num - 1; i++)
    {
        for (int j = i + 1; j < seq_num; j++)
        {
            Pair p(i, j);
            PairAlign *a = new PairAlign(p, seq->get_seq(i), seq->get_seq(j));
            mAligns.push_back(a);
        }
    }
    std::cout << "done!\n";
    return;
}

/*!
 * Return a h-value to the Coord \a c using HPair logic.
 * H is the sum of all pairwise values based on reverse strings.
 */
template <int N>
int HeuristicHPair::calculate_h(const Coord<N> &c) const
{
    int h = 0;
    for (std::vector<PairAlign*>::const_iterator it = mAligns.begin() ; it != mAligns.end(); ++it)
    {
        int x = (*it)->getPair().first;
        int y = (*it)->getPair().second;

        h += (*it)->getScore(c[x], c[y]);
    }
    return h;
}

#define DECLARE_TEMPLATE( X ) \
template int HeuristicHPair::calculate_h< X >(Coord< X > const&) const;

MAX_NUM_SEQ_HELPER(DECLARE_TEMPLATE);

#include <iostream>

#include "Coord.h"
#include "HeuristicHPair.h"
#include "PairAlign.h"
#include "Sequences.h"

HeuristicHPair* HeuristicHPair::instance = NULL;

HeuristicHPair::HeuristicHPair()
{
    mAligns.clear();
}

HeuristicHPair::~HeuristicHPair()
{
    for (vector<PairAlign*>::iterator it = mAligns.begin() ; it != mAligns.end(); ++it)
        delete *it;
}

HeuristicHPair* HeuristicHPair::getInstance()
{
    if (!instance)
        instance = new HeuristicHPair();
    return instance;
}

void HeuristicHPair::destroyInstance()
{
    delete instance;
    instance = NULL;
}

void HeuristicHPair::init()
{
    Sequences *seq = Sequences::getInstance();
    int seq_num = Sequences::get_seq_num();
    setHeuristic(instance);

    cout << "Starting pairwise alignments... " << flush;
    for (int i = 0; i < seq_num - 1; i++)
    {
        for (int j = i + 1; j < seq_num; j++)
        {
            Pair p(i, j);
            PairAlign *a = new PairAlign(p, seq->get_seq(i), seq->get_seq(j));
            mAligns.push_back(a);
        }
    }
    cout << "done!\n";
    return;
}

int HeuristicHPair::calculate_h(const Coord &c) const
{
    int h = 0;
    for (vector<PairAlign*>::const_iterator it = mAligns.begin() ; it != mAligns.end(); ++it)
    {
        int x = (*it)->getPair().first;
        int y = (*it)->getPair().second;

        h += (*it)->getScore(c[x], c[y]);
    }
    return h;
}

#ifndef _PAIRALIGN_H
#define _PAIRALIGN_H
#include <string>

#include "Sequences.h"

typedef pair<int,int> Pair;

class PairAlign {
    private:
        int m_matrix[MAX_SEQ_SIZE][MAX_SEQ_SIZE];
        Pair m_par;
        void Align(const string &s1, const string &s2);

    public:
        const Pair& getPair() const { return m_par; };
        int getScore(const int i, const int j) const;
        PairAlign();
        PairAlign(Pair p, const string &s1, const string &s2);
};

#endif

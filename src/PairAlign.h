/*!
 * \class PairAlign
 * \filename PairAlign.h
 * \author Daniel Sundfeld
 *
 * \brief Calculate an pairwise alignment and saves all scores on a 2D matrix
 *
 * INSERT_LICENSE
 */
#ifndef _PAIRALIGN_H
#define _PAIRALIGN_H
#include <string>

using namespace std;

typedef pair<int,int> Pair;

class PairAlign {
    private:
        int **m_matrix;
        int s1_l, s2_l;
        Pair m_par;
        void Align(const string &s1, const string &s2);
        void freeMemory();
        void initMatrix(int size1, int size2);

    public:
        PairAlign();
        ~PairAlign();
        const Pair& getPair() const { return m_par; };
        int getScore(const int i, const int j) const;
        PairAlign(Pair p, const string &s1, const string &s2);
};

#endif

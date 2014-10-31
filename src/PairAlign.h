/*!
 * \class PairAlign
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Calculate an pairwise alignment and saves all scores on a 2D matrix
 */
#ifndef _PAIRALIGN_H
#define _PAIRALIGN_H
#include <string>

typedef std::pair<int,int> Pair;

class PairAlign {
    public:
        PairAlign(Pair p, const std::string &s1, const std::string &s2);
        ~PairAlign();
        friend std::ostream& operator<<(std::ostream &lhs, const PairAlign &rhs);

        const Pair& getPair() const { return m_par; };
        int getScore(const int i, const int j) const;

    private:
        enum { NoGap, GapX, GapY }; //!< m_affine_matrix values
        int **m_matrix;
        int **m_affine_matrix;

        int s1_l, s2_l;
        Pair m_par;
        void Align(const std::string &s1, const std::string &s2);
        void destroyScoreMatrix();
        void destroyAffineMatrix();
        void initMatrix(int size1, int size2);
        void initScoreMatrix();
        void initAffineMatrix();
        int gapCost(int i, int j, int destination);
        void pairCost(int i, int j, const std::string &s1, const std::string &s2);
};
#endif

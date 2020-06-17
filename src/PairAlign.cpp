/*!
 * \class PairAlign
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "PairAlign.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

#include "Cost.h"

/*!
 * Creates a pair align of the sequences \a s1 and \a s2.
 * It is important to remember which sequences we are using, so save this
 * infomation as the pair \a p
 */
PairAlign::PairAlign(Pair p, const std::string &s1, const std::string &s2)
:   m_par(p)
{
//    cout << "Pairwise alignment: " << p.first << " " << p.second << std::endl << s1 << std::endl << s2 << std::endl;
    Align(s1, s2);
//    cout << "Score: " << m_matrix[0][0] << std::endl;
}

PairAlign::~PairAlign()
{
    destroyScoreMatrix();
}

/*! 
 * Print the pairwise matrix on screen. Hopefully debug only. You have problems
 * if you use this function for other purpose.
 */
std::ostream& operator<<(std::ostream &lhs, const PairAlign &rhs)
{
    lhs << "Pair: " << rhs.m_par.first << "/" << rhs.m_par.second << std::endl;
    for (int i = 0; i <= rhs.s1_l; i++)
    {
        int j;
        for (j = 0; j <= rhs.s2_l; j++)
            lhs << std::setfill('0') << std::setw(2) << rhs.m_matrix[i][j] << " ";
        lhs << "(" << i << " " << j << ")" << std::endl;
    }
    return lhs;
}

//! Initialize all internal matrixes with sizes \a size1 and \a size2
void PairAlign::initMatrix(int size1, int size2)
{
    s1_l = size1;
    s2_l = size2;

    initScoreMatrix();
}

//! Initialize the internal matrix
void PairAlign::initScoreMatrix()
{
    m_matrix = new int*[s1_l + 1];
    for (int i = 0; i < s1_l + 1; i++)
        m_matrix[i] = new int[s2_l + 1];
}

//! Free memory usage by the matrix
void PairAlign::destroyScoreMatrix()
{
    for (int i = 0; i <= s1_l; i++)
        delete[] m_matrix[i];
    delete[] m_matrix;
}

/*!
 * Helper function to calculate and save on the matrix the cost of
 * the cell with coord \a x and \a y
 */
void PairAlign::pairCost(int i, int j, const std::string &s1, const std::string &s2)
{
    int min_value;

    int c0 = m_matrix[i+1][j] + Cost::GapCost;
    int c1 = m_matrix[i][j+1] + Cost::GapCost;
    if (c0 < c1)
    {
        min_value = c0;
    }
    else
    {
        min_value = c1;
    }

    int c2 = m_matrix[i+1][j+1] + Cost::cost(s1.at(i), s2.at(j));
    if (c2 < min_value)
    {
        min_value = c2;
    }

    m_matrix[i][j] = min_value;
}

//! Do a pairwise alignment
void PairAlign::Align(const std::string &s1, const std::string &s2)
{
    int i, j;
    initMatrix(s1.length(), s2.length());

    m_matrix[s1_l  ][s2_l  ] = 0;
    m_matrix[s1_l  ][s2_l-1] = Cost::GapCost;
    m_matrix[s1_l-1][s2_l  ] = Cost::GapCost;

    for (j = s2_l-2; j >= 0; j--)
    {
        m_matrix[s1_l][j] = m_matrix[s1_l][j+1] + Cost::GapCost;
    }

    for (i = s1_l-2; i >= 0; i--)
    {
        m_matrix[i][s2_l] = m_matrix[i+1][s2_l] + Cost::GapCost;
    }

    for (i = s1_l-1; i >= 0; i--)
    {
        for (j = s2_l-1; j >= 0; j--)
        {
            pairCost(i, j, s1, s2);
        }
    }
    //cout << std::endl << *this;
}

//! Return the value of the 2D-matrix with coords i and j
int PairAlign::getScore(const int i, const int j) const
{
    return m_matrix[i][j];
}

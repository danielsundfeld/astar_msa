/*!
 * \filename PairAlign.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

#include "Cost.h"
#include "PairAlign.h"

using namespace std;

PairAlign::PairAlign()
{
}

PairAlign::~PairAlign()
{
    freeMemory();
}

//! Initialize the internal matrix with sizes \a size1 and \a size2
void PairAlign::initMatrix(int size1, int size2)
{
    s1_l = size1;
    s2_l = size2;

    m_matrix = new int*[size1 + 1];
    for (int i = 0; i < size1 + 1; i++)
        m_matrix[i] = new int[size2 + 1];
}

//! Free memory usage by the matrix
void PairAlign::freeMemory()
{
    for (int i = 0; i <= s1_l; i++)
        delete[] m_matrix[i];
    delete[] m_matrix;
}

//! Do a pairwise alignment
void PairAlign::Align(const string &s1, const string &s2)
{
    int i, j;
    initMatrix(s1.length(), s2.length());

    m_matrix[s1_l][s2_l] = 0;

    for (j = s2_l-1; j >= 0; j--)
        m_matrix[s1_l][j] = m_matrix[s1_l][j+1] + Cost::GAP;

    for (i = s1_l-1; i >= 0; i--)
        m_matrix[i][s2_l] = m_matrix[i+1][s2_l] + Cost::GAP;

    for (i = s1_l-1; i >= 0; i--)
    {
        for (j = s2_l-1; j >= 0; j--)
        {
            int c0 = m_matrix[i+1][j]   + Cost::GAP;
            int c1 = m_matrix[i]  [j+1] + Cost::GAP;
            int c2 = m_matrix[i+1][j+1] + Cost::cost(s1.at(i), s2.at(j));

            m_matrix[i][j] = min(c0, min(c1, c2));
        }
    }
/*    // Debug code to print pairwise matrix
    cout << endl;
    for (i = 0; i <= s1_l; i++)
    {
        for (j = 0; j <= s2_l; j++)
        {
            cout << setfill('0') << setw(2) << m_matrix[i][j] << " ";
        }
        cout << "(" << i << " " << j << ")" << endl;
    }
*/
}

//! Return the value of the 2D-matrix with coords i and j
int PairAlign::getScore(const int i, const int j) const
{
    return m_matrix[i][j];
}

/*!
 * Creates a pair align of the sequences \a s1 and \a s2.
 * It is important to remember wich sequences are using, so save this
 * infomation as the pair \a p
 */
PairAlign::PairAlign(Pair p, const string &s1, const string &s2)
:   m_par(p)
{
    
//    cout << "Pairwise alignment: " << p.first << " " << p.second << endl << s1 << endl << s2 << endl;
    Align(s1, s2);
//    cout << "Score: " << m_matrix[0][0] << endl;
}

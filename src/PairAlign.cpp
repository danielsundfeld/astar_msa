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

void PairAlign::Align(const string &s1, const string &s2)
{
    int i;
    int j;
    int s1_l = (int)s1.length();
    int s2_l = (int)s2.length();

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
/*
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

int PairAlign::getScore(const int i, const int j) const
{
    return m_matrix[i][j];
}

PairAlign::PairAlign(Pair p, const string &s1, const string &s2)
:   m_par(p)
{
    
//    cout << "Pairwise alignment: " << p.first << " " << p.second << endl << s1 << endl << s2 << endl;
    Align(s1, s2);
//    cout << "Score: " << m_matrix[0][0] << endl;
}



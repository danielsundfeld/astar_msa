/*!
 * \class Cost
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class that calculates match, mismatch and gap cost
 */
#ifndef _COST_H
#define _COST_H
class Cost {
    public:
        Cost();
        enum { GapExtension = 30, GapOpen = 30, GapGap = GapOpen };

        //! Do not use char as array subscripts, this enum 'cast' them to integer
        enum {
            A = 'A',
            B = 'B',
            C = 'C',
            D = 'D',
            E = 'E',
            F = 'F',
            G = 'G',
            H = 'H',
            I = 'I',
            J = 'J',
            K = 'K',
            L = 'L',
            M = 'M',
            N = 'N',
            O = 'O',
            P = 'P',
            Q = 'Q',
            R = 'R',
            S = 'S',
            T = 'T',
            U = 'U',
            V = 'V',
            W = 'W',
            X = 'X',
            Y = 'Y',
            Z = 'Z'
        };

        static int cost(const char r, const char l);

    private:
        static int pam250['Z']['Z'];
};
#endif

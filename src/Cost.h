/*!
 * \class Cost
 * \filename Cost.h
 * \author Daniel Sundfeld
 * \brief Class that calculates match, mismatch and gap cost
 *
 * INSERT_LICENSE
 */
#ifndef _COST_H
#define _COST_H
class Cost {
    public:
        /* Naive cost enum */
        enum { MATCH = 0, MISMATCH = 1, GAP = 2, GapExtension = 2, GapOpen = 5 };

        static int cost(const char r, const char l);
};
#endif

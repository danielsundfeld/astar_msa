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

        static int cost(const char r, const char l);

    private:
        static int pam250['Z']['Z'];
};
#endif

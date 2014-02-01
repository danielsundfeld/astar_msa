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
    private:
        static int pam250['Z']['Z'];

    public:
        Cost();
        enum { GapExtension = 12, GapOpen = 25 };

        static int cost(const char r, const char l);
};
#endif

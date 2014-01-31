/*!
 * \class Cost
 * \filename Cost.h
 * \author Daniel Sundfeld
 *
 * \brief Class that calculates match, mismatch and gap cost
 *
 * INSERT_LICENSE
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

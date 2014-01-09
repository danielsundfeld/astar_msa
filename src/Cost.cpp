/*!
 * \filename Cost.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include "Cost.h"

//! Compare \a r and \a l and return the cost.
int Cost::cost(const char r, const char l)
{
    if (r == l)
        return MATCH;
    return MISMATCH;
}

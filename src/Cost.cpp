/*!
 * \filename Cost.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include "Cost.h"

int Cost::cost(const char r, const char l)
{
    if (r == l)
        return MATCH;
    return MISMATCH;
}


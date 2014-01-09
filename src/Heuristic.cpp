/*!
 * \filename Heuristic.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include "Heuristic.h"

//! Singleton instance
Heuristic* Heuristic::instance = NULL;

Heuristic::~Heuristic()
{
}

//! Return the current heuristic
Heuristic* Heuristic::getHeuristic()
{
    return instance;
}

//! Set the current heuristic as \a p
void Heuristic::setHeuristic(Heuristic *p)
{
    instance = p;
}

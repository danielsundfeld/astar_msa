/*!
 * \class SingletonKeep
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * This file contains SingletonKeep instances to grants that
 * singletons are created before main starts and it is destroyed
 * when the program ends. The order is not guaranteed by the C++
 * language.
 */
#ifndef _SINGLETONKEEPVARIABLES_H
#define _SINGLETONKEEPVARIABLES_H
#include "HeuristicHPair.h"
#include "Sequences.h"

static SingletonKeep<Sequences> sequenceskeeper;
static SingletonKeep<HeuristicHPair> heuristichpairkeeper;
#endif

#ifndef _SINGLETONKEEPVARIABLES_H
#define _SINGLETONKEEPVARIABLES_H
#include "HeuristicAllP2.h"
#include "Sequences.h"

/*! 
 * This file contains SingletonKeep instances to grants that 
 * singletons are created before main starts and it is destroyed 
 * when the program ends. The order is not guaranteed by the C++ 
 * language.
 */

static SingletonKeep<Sequences> sequenceskeeper;
static SingletonKeep<HeuristicAllP2> heuristicallp2keeper;
#endif

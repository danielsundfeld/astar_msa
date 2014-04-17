#ifndef _PSTAR_H
#define _PSTAR_H
/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Coord.h"
#include "Node.h"

#define search_function pa_star

const string initial_message("Performing search with Parallel A-Star.\n");

int pa_star(const Node &node_zero, bool(*is_final)(const Coord &c));
#endif

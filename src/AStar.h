#ifndef _ASTAR_H
#define _ASTAR_H
/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Coord.h"
#include "Node.h"

#define search_function a_star

const string initial_message("Performing search with Serial A-Star.\n");

int a_star(const Node &node_zero, bool(*is_final)(const Coord &c));
#endif

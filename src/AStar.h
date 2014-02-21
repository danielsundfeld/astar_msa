#ifndef _ASTAR_H
#define _ASTAR_H
/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Coord.h"
#include "Node.h"

int a_star(const Node &node_zero, bool(*is_final)(const Coord &c));
#endif

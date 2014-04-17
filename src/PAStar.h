#ifndef _PSTAR_H
#define _PSTAR_H
/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Coord.h"
#include "Node.h"

int pa_star(const Node &node_zero, bool(*is_final)(const Coord &c));
#endif

#ifndef _PFA2DDD_H
#define _PFA2DDD_H
/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "Coord.h"
#include "Node.h"

int pfa2ddd(const Node &node_zero, bool(*is_final)(const Coord &c));
#endif

/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef _ASTAR_H
#define _ASTAR_H
#include <string>

#include "Coord.h"
#include "Node.h"

template <int N> int a_star(const Node<N> &node_zero, bool(*is_final)(const Coord<N> &c));
#endif

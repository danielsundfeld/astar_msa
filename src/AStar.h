/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef _ASTAR_H
#define _ASTAR_H
#include <string>

#include "Coord.h"
#include "Node.h"

#define search_function a_star

const std::string initial_message("Performing search with Serial A-Star.\n");

template <int N> int a_star(const Node<N> &node_zero, bool(*is_final)(const Coord<N> &c));
#endif

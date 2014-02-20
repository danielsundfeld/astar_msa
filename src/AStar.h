#ifndef _ASTAR_H
#define _ASTAR_H
/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <map>
#include <queue>
#include <vector>

#include "Coord.h"
#include "Node.h"

using namespace std;

typedef map<Coord, Node> ListType;
typedef priority_queue<Node, vector<Node>, PriorityNode> PriorityType;

int a_star(const Node &node_zero, bool(*is_final)(const Coord &c));
#endif

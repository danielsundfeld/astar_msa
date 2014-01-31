#ifndef _ASTAR_H
#define _ASTAR_H
/*!
 * \filename AStar.h
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include <map>
#include <queue>
#include <vector>

#include "Coord.h"
#include "Node.h"

using namespace std;

typedef map<Coord, Node> ListType;
typedef priority_queue<Node, vector<Node>, PriorityNode> PriorityType;

int a_star();
#endif

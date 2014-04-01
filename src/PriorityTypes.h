#ifndef _PRIORITYTYPES_H
#define _PRIORITYTYPES_H
/*!
 * \class PriorityTypes
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Usefull typedefs for PriorityList
 */
#include <map>
#include <queue>

#include "Coord.h"
#include "Node.h"

using namespace std;

typedef map<Coord, Node> ListType;
#ifdef NO_LIB_BOOST
typedef priority_queue<Node, vector<Node>, PriorityNode> PriorityType;
#endif

//! ClosedList is always a STL map
typedef ListType::const_iterator closed_list_iterator;
#endif

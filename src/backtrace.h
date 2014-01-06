/*!
 * \filename Backtrace.h
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#ifndef _BACKTRACE_H
#define _BACKTRACE_H
#include <map>

#include "Coord.h"
#include "Node.h"

void backtrace(std::map<Coord, Node> &ClosedList);
#endif

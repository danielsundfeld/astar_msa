/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef _BACKTRACE_H
#define _BACKTRACE_H
#include <boost/unordered_map.hpp>

#include "Coord.h"
#include "Node.h"

template <int N> void backtrace(boost::unordered_map< Coord<N>, Node<N> > *ClosedList, int list_size = 1);
#endif

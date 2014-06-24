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

#include "Coord.h"
#include "Node.h"

template <int N>
struct List {
      typedef std::map<Coord<N>, Node<N> > type;
};
#endif

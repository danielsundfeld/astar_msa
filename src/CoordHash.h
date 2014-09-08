/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Hash functions to Class Coord
 */
#ifndef _COORD_HASH_H
#define _COORD_HASH_H

#ifdef HASHFSUM
const char hash_name_pretty[] = "Full-Sum";
#elif HASHPSUM
const char hash_name_pretty[] = "Partial-Sum";
#elif HASHPZORDER
const char hash_name_pretty[] = "Partial-Zorder";
#else
const char hash_name_pretty[] = "Full-Zorder";
#endif

#ifndef HASH_SHIFT
    //! The size of the shift on most hash functions
    #define HASH_SHIFT  12
#endif

#endif

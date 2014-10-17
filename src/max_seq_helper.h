#ifndef _MAX_SEQ_HELPER_H
#define _MAX_SEQ_HELPER_H

// For every desirable sequences size, maybe we have some code dependend on the
// number of sequences.
// For instance, we must declare many templates. Use this macro as a helper.
// See examples on Coord.cpp file. This is just in the case that you
// implement template on the .cpp
#define MAX_NUM_SEQ_HELPER( X ) \
X(3); \
X(4); \
X(5); \
X(6); \
X(7); \
X(8); \
X(9); \
X(10); \
X(14); \
X(16); \

#endif

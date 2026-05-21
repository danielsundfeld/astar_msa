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
X(11); \
X(12); \
X(13); \
X(14); \
X(15); \
X(16); \
X(17); \
X(18); \
X(19); \
X(20); \
X(21); \
X(22); \
X(23); \
X(24); \
X(25); \
X(26); \
X(27); \
X(28); \
X(29); \
X(30); \

#endif

#ifndef _MAX_SEQ_TEMPLATE_HELPER
#define _MAX_SEQ_TEMPLATE_HELPER

// If you use a Coord, probably have to be a template class or method.
// For every desirable sequences size, we must declare many templates.
// use this macro as a helper. See examples on Coord.cpp file
// This is just in the case that you implement template on the .cpp
#define MAX_NUM_SEQ_TEMPLATE_HELPER( X ) \
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

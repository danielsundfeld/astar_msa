#ifndef _COST_H
#define _COST_H
class Cost {
    public:
        /* Naive cost enum */
        enum { MATCH = 0, MISMATCH = 1, GAP = 2 };

        static int cost(const char r, const char l);
};
#endif
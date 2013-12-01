#ifndef _SEQUENCES_H
#define _SEQUENCES_H
#include <string>
#include <vector>
#include "Coord.h"

using namespace std;

class Sequences
{
    private:
        unsigned int n_seq;
        static Sequences *instance;
        Sequences();
        vector<string> seqs;
        Coord final_coord;

    public:
        enum { MATCH = 0, MAX_MISMATCH = 1, GAP = 2 };
        static Sequences *getInstance()
        {
            if (!instance) instance = new Sequences();
            return instance;
        }
        Coord get_final_coord() { return final_coord; };
        string get_seq(int x) { return seqs.at(x); };
        unsigned int get_seq_num() { return n_seq; };
        int set_seq(string x);

        int cost(char r, char l);
        int cost_mismatch(char r, char l);
        bool is_not_final(Coord c);
        void destroy();
};
#endif

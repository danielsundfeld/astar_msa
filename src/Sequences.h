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
        enum { MATCH = 0, GAP = 2 };
        static Sequences *getInstance()
        {
            if (!instance) instance = new Sequences();
            return instance;
        }
        string get_seq(int x) { return seqs.at(x); };
        int set_seq(string x);
        unsigned int get_seq_num() { return n_seq; };
        int cost(char r, char l);
        int cost_mismatch(char r, char l);
        bool is_not_final(Coord c);
};
#endif

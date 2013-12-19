#ifndef _SEQUENCES_H
#define _SEQUENCES_H
#include <string>
#include <vector>
#include "Coord.h"

using namespace std;

#define MAX_SEQ_SIZE    1000

class Sequences
{
    private:
        static unsigned int n_seq;
        static Sequences *instance;
        Sequences();
        vector<string> seqs;
        Coord final_coord;

    public:
        static Sequences *getInstance();
        static void destroyInstance();
        int set_seq(string x);
        const Coord& get_final_coord() const { return final_coord; };
        const string& get_seq(int x) const { return seqs.at(x); };
        static unsigned int& get_seq_num() { return n_seq; };
        bool is_final(const Coord &c) const;
};
#endif

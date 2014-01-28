/*!
 * \class Sequences
 * \filename Sequences.h
 * \author Daniel Sundfeld
 * \brief Singleton that holds all sequences being aligned
 *
 * INSERT_LICENSE
 */
#ifndef _SEQUENCES_H
#define _SEQUENCES_H
#include <string>
#include <vector>
#include "Coord.h"
#include "Node.h"

using namespace std;

class Sequences
{
    private:
        static unsigned int n_seq;
        static Sequences *instance;
        Sequences();
        vector<string> seqs;
        static Coord final_coord;
        static Coord initial_coord;

    public:
        static Sequences *getInstance();
        static void destroyInstance();
        int set_seq(const string &x);
        static const Coord& get_final_coord() { return final_coord; };
        static const Coord& get_initial_coord() { return initial_coord; };
        const string& get_seq(int x) const { return seqs.at(x); };
        static unsigned int& get_seq_num() { return n_seq; };
        static Node get_initial_node();
        bool is_final(const Coord &c) const;
};
#endif

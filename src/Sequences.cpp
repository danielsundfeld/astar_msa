#include <iostream>
#include <string>
#include "Coord.h"
#include "Sequences.h"

using namespace std;

Sequences::Sequences()
{
    n_seq = 0;
}

Sequences* Sequences::instance = NULL;

int Sequences::cost_mismatch(char r, char l)
{
    return 1;
}

int Sequences::cost(char r, char l)
{
    if (r == l)
        return MATCH;
    return cost_mismatch(r, l);
}

int Sequences::set_seq(string x)
{
    seqs.push_back(x);
    ++n_seq;

    if (n_seq == 3)
       final_coord = Coord(get_seq(0).length(), get_seq(1).length(), get_seq(2).length()); 
    return n_seq;
}

bool Sequences::is_not_final(Coord c)
{
    return !(c == final_coord);
}


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

Sequences* Sequences::getInstance()
{
    if (!instance)
        instance = new Sequences();
    return instance;
}

int Sequences::cost_mismatch(const char r, const char l) const
{
    return 1;
}

int Sequences::cost(const char r, const char l) const
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

bool Sequences::is_not_final(const Coord &c) const
{
    return !(c == final_coord);
}

void Sequences::destroy()
{
    delete instance;
    instance = NULL;
}


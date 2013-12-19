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

void Sequences::destroyInstance()
{
    delete instance;
    instance = NULL;
}

int Sequences::set_seq(string x)
{
    seqs.push_back(x);
    ++n_seq;

    if (n_seq == 3)
       final_coord = Coord(get_seq(0).length(), get_seq(1).length(), get_seq(2).length()); 
    return n_seq;
}

bool Sequences::is_final(const Coord &c) const
{
    return (c == final_coord);
}

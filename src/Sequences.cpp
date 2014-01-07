/*!
 * \filename Sequences.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include <iostream>
#include <string>

#include "Coord.h"
#include "Sequences.h"

using namespace std;

Sequences::Sequences()
{
    n_seq = 0;
}

unsigned int Sequences::n_seq = 0;
Sequences* Sequences::instance = NULL;
Coord Sequences::final_coord;

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

int Sequences::set_seq(const string &x)
{
    seqs.push_back(x);
    ++n_seq;

    final_coord.append(x.length());
    return n_seq;
}

bool Sequences::is_final(const Coord &c) const
{
    return (c == final_coord);
}

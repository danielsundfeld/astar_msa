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

//! Number of sequences
unsigned int Sequences::n_seq = 0;
//! Singleton instance
Sequences* Sequences::instance = NULL;
//! Source coord
Coord Sequences::initial_coord;
//! Destination coord
Coord Sequences::final_coord;

//! Return the instance, creates if it doesn't exist
Sequences* Sequences::getInstance()
{
    if (!instance)
        instance = new Sequences();
    return instance;
}

//! Destroy the instance
void Sequences::destroyInstance()
{
    delete instance;
    instance = NULL;
    n_seq = 0;
    final_coord.clear();
    initial_coord.clear();
}

//! Save the string \a x as an Sequence
int Sequences::set_seq(const string &x)
{
    seqs.push_back(x);
    ++n_seq;

    initial_coord.append(0);
    final_coord.append(x.length());
    return n_seq;
}

//! Check if \a c is the destination
bool Sequences::is_final(const Coord &c) const
{
    return (c == final_coord);
}

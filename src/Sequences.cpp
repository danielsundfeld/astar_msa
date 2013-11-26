#include <string>
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
    return ++n_seq;
}


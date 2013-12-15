#include "Heuristic.h"

Heuristic* Heuristic::instance = NULL;

Heuristic::~Heuristic()
{
}

Heuristic* Heuristic::getHeuristic()
{
    return instance;
}

void Heuristic::setHeuristic(Heuristic *p)
{
    instance = p;
}


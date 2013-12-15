#include <iostream>

#include "Coord.h"
#include "Cost.h"
#include "HeuristicAllP2.h"
#include "Sequences.h"

HeuristicAllP2 heuristic;

HeuristicAllP2::HeuristicAllP2()
{
    cout << "Iniciando\n";
}

HeuristicAllP2::~HeuristicAllP2()
{
    cout << "Terminando\n";
}

void HeuristicAllP2::init()
{
    return;
}

int HeuristicAllP2::calculate_heuristic(const Coord &c) const
{
    Coord final = Sequences::getInstance()->get_final_coord();
    int delta_x = final.get_x() - c.get_x();
    int delta_y = final.get_y() - c.get_y();
    int delta_z = final.get_z() - c.get_z();

    int min_delta = min(delta_x, min(delta_y, delta_z));
    return (delta_x + delta_y + delta_z - 3 * min_delta) * Cost::GAP;
}

int HeuristicAllP2::calculate_h(const Coord &c)
{
    return heuristic.calculate_heuristic(c);
}


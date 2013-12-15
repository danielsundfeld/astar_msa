#include "Coord.h"
#include "Cost.h"
#include "HeuristicAllP2.h"
#include "Sequences.h"

HeuristicAllP2* HeuristicAllP2::instance = NULL;

HeuristicAllP2::HeuristicAllP2()
{
    m_seq = Sequences::getInstance();
}

HeuristicAllP2::~HeuristicAllP2()
{
}

HeuristicAllP2* HeuristicAllP2::getInstance()
{
    if (!instance)
        instance = new HeuristicAllP2();
    return instance;
}

void HeuristicAllP2::destroyInstance()
{
    delete instance;
    instance = NULL;
}

void HeuristicAllP2::init()
{
    setHeuristic(instance);
    return;
}

int HeuristicAllP2::calculate_h(const Coord &c) const
{
    Coord final = m_seq->get_final_coord();
    int delta_x = final.get_x() - c.get_x();
    int delta_y = final.get_y() - c.get_y();
    int delta_z = final.get_z() - c.get_z();

    int min_delta = min(delta_x, min(delta_y, delta_z));
    return (delta_x + delta_y + delta_z - 3 * min_delta) * Cost::GAP;
}


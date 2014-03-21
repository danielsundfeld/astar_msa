/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief The main fuction from the MSA-A-Star project
 */
#include <iostream>

using namespace std;

#include "AStar.h"
#include "HeuristicHPair.h"
#include "read_fasta.h"
#include "PFA2DDD.h"

int usage(char progname[])
{
    cout << "Usage:\n" << progname << " <fasta_file>\n";
    return -1;
}

int main(int argc, char *argv[])
{
    if ((argc == 1) || (read_fasta_file(argv[1]) != 0))
        return usage(argv[0]);

    HeuristicHPair::getInstance()->init();

    if (argc == 2)
    {
        cout << "Sequential code...\n";
        return a_star(Sequences::get_initial_node(), Sequences::is_final);
    }
    else
    {
        cout << "Parallel code...\n";
        return pfa2ddd(Sequences::get_initial_node(), Sequences::is_final);
    }
}

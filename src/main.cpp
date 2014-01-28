/*!
 * \filename main.cpp
 * \author Daniel Sundfeld
 *
 * \brief The main fuction from the MSA-A-Star project
 *
 * INSERT_LICENSE
 */
#include <iostream>

using namespace std;

#include "AStar.h"
#include "HeuristicHPair.h"
#include "read_fasta.h"

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

    return a_star();
}


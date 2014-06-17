/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief The main function for msa_pastar project
 */
#include <iostream>

using namespace std;

#include "HeuristicHPair.h"
#include "PAStar.h"
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

    cout << initial_message;
    return PAStar::pa_star(Sequences::get_initial_node(), Sequences::is_final);
}

/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief The main function for msa_pastar project
 */
#include <iostream>

#include "HeuristicHPair.h"
#include "PAStar.h"
#include "Sequences.h"
#include "read_fasta.h"

int usage(char progname[])
{
    std::cout << "Usage:\n" << progname << " <fasta_file>\n";
    return -1;
}

int pa_star_run(const PAStarOpt &opt)
{
    switch (Sequences::get_seq_num())
    {
        case 3:
            return PAStar<3>::pa_star(Sequences::get_initial_node<3>(), Sequences::is_final, opt);
        case 4:
            return PAStar<4>::pa_star(Sequences::get_initial_node<4>(), Sequences::is_final, opt);
        case 5:
            return PAStar<5>::pa_star(Sequences::get_initial_node<5>(), Sequences::is_final, opt);
        case 6:
            return PAStar<6>::pa_star(Sequences::get_initial_node<6>(), Sequences::is_final, opt);
        case 7:
            return PAStar<7>::pa_star(Sequences::get_initial_node<7>(), Sequences::is_final, opt);
        case 8:
            return PAStar<8>::pa_star(Sequences::get_initial_node<8>(), Sequences::is_final, opt);
        case 9:
            return PAStar<9>::pa_star(Sequences::get_initial_node<9>(), Sequences::is_final, opt);
        case 10:
            return PAStar<10>::pa_star(Sequences::get_initial_node<10>(), Sequences::is_final, opt);
        default:
            std::cout << "Invalid number of sequences: " << Sequences::get_seq_num() << std::endl;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    PAStarOpt opt;
    if ((argc == 1) || (read_fasta_file(argv[1]) != 0))
        return usage(argv[0]);

    HeuristicHPair::getInstance()->init();

    std::cout << initial_message;
    return pa_star_run(opt);
}

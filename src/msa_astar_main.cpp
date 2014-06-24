/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief The main function for the msa_astar project
 */
#include <iostream>

#include "AStar.h"
#include "HeuristicHPair.h"
#include "read_fasta.h"

int usage(char progname[])
{
    std::cout << "Usage:\n" << progname << " <fasta_file>\n";
    return -1;
}

int a_star_run()
{
    switch (Sequences::get_seq_num())
    {
        case 3:
            return a_star<3>(Sequences::get_initial_node<3>(), Sequences::is_final);
        case 4:
            return a_star<4>(Sequences::get_initial_node<4>(), Sequences::is_final);
        case 5:
            return a_star<5>(Sequences::get_initial_node<5>(), Sequences::is_final);
        case 6:
            return a_star<6>(Sequences::get_initial_node<6>(), Sequences::is_final);
        case 7:
            return a_star<7>(Sequences::get_initial_node<7>(), Sequences::is_final);
        case 8:
            return a_star<8>(Sequences::get_initial_node<8>(), Sequences::is_final);
        case 9:
            return a_star<9>(Sequences::get_initial_node<9>(), Sequences::is_final);
        case 10:
            return a_star<10>(Sequences::get_initial_node<10>(), Sequences::is_final);
        default:
            std::cout << "Invalid number of sequences: " << Sequences::get_seq_num() << std::endl;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if ((argc == 1) || (read_fasta_file(argv[1]) != 0))
        return usage(argv[0]);

    HeuristicHPair::getInstance()->init();

    std::cout << initial_message;
    return a_star_run();
}

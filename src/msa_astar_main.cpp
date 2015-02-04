/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief The main function for the msa_astar project
 */
#include <iostream>

#include "AStar.h"
#include "HeuristicHPair.h"
#include "max_seq_helper.h"
#include "msa_options.h"
#include "Sequences.h"
#include "read_fasta.h"

int a_star_run_core(const AStarOpt &opt)
{
    HeuristicHPair::getInstance()->init();

    // This macro is expanded to every supported number of sequences
    #define RUN_ASTAR(X) \
        case X : \
            return a_star< X >(Sequences::get_initial_node< X >(), Sequences::get_final_coord< X >(), opt);

    std::cout << "Performing search with Serial A-Star.\n";
    switch (Sequences::get_seq_num())
    {
        MAX_NUM_SEQ_HELPER( RUN_ASTAR );
        default:
            std::cerr << "Fatal error: Invalid number of sequences: " << Sequences::get_seq_num() << std::endl;
    }
    return -1;
}

int a_star_run(const AStarOpt &opt)
{
    try
    {
        return a_star_run_core(opt);
    }
    catch (std::exception &e)
    {
        std::cerr << "Running fatal error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error while running!\n";
    }
    return -1;
}

int main(int argc, char *argv[])
{
    AStarOpt opt;
    std::string filename;

    if (msa_astar_options(argc, argv, filename, opt) != 0)
        return 1;
    if (read_fasta_file(filename) != 0)
        return 1;
    return a_star_run(opt);
}

/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief The main function for msa_pastar project
 */
#include <iostream>

#include "HeuristicHPair.h"
#include "max_seq_helper.h"
#include "msa_options.h"
#include "PAStar.h"
#include "Sequences.h"
#include "read_fasta.h"

int pa_star_run_core(const PAStarOpt &opt)
{
    HeuristicHPair::getInstance()->init();

    // This macro is expanded to every supported number of sequences
    #define RUN_PASTAR(X) \
        case X : \
            return PAStar< X >::pa_star(Sequences::get_initial_node< X >(), Sequences::get_final_coord< X >(), opt);

    std::cout << "Performing search with Parallel A-Star.\n";
    switch (Sequences::get_seq_num())
    {
        MAX_NUM_SEQ_HELPER( RUN_PASTAR );
        default:
            std::cerr << "Fatal error: Invalid number of sequences: " << Sequences::get_seq_num() << std::endl;
    }
    return -1;
}

int pa_star_run(const PAStarOpt &opt)
{
    try
    {
        return pa_star_run_core(opt);
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
    PAStarOpt opt;
    std::string filename;

    if (msa_pastar_options(argc, argv, filename, opt) != 0)
        return 1;
    if (read_fasta_file(filename) != 0)
        return 1;
    return pa_star_run(opt);
}

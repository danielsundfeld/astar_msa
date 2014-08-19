/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Parse the arguments options for the msa programs
 */
#include <boost/program_options.hpp>

#include "msa_options.h"

namespace po = boost::program_options;

//! Arguments parse core functions
int msa_options_core(int type, int argc, char *argv[], std::string &filename, int &threads_num)
{
    const std::string description = "Usage " + std::string(argv[0]) + " [OPTIONS] file.fasta";

    // Arguments Options
    po::options_description common_options("Options");
    common_options.add_options()
        ("version,v", "print version string")
        ("help,h", "produce help message")
        ;

    // config file
    po::options_description parallel_options("Parallel Options");
    parallel_options.add_options()
        ("threads,t", po::value<int>(&threads_num),
         "number of threads")
        ;

    // Fasta File Name
    po::options_description input_fasta_file;
    input_fasta_file.add_options()
        ("file.fasta", po::value<std::string>(&filename), "fasta filename")
        ;

    // Acceptable arguments
    po::options_description all_options;
    all_options.add(common_options).add(input_fasta_file);
    if (type == Msa_Pastar)
        all_options.add(parallel_options);

    // The description on how to use
    po::options_description usage(description);
    usage.add(common_options);
    if (type == Msa_Pastar)
        usage.add(parallel_options);

    // file.fasta is position independet
    po::positional_options_description p;
    p.add("file.fasta", -1);

    // Now, parse
    po::variables_map vm;
    store(po::command_line_parser(argc, argv).
            options(all_options).positional(p).run(), vm);
    notify(vm);

    // And now, verify
    if (vm.count("help") || !vm.count("file.fasta"))
    {
        std::cout << usage << std::endl;
        return 1;
    }
    if (vm.count("version")) {
        std::cout << "msa_pastar, version 0.0\n";
        return 1;
    }
    return 0;
}

//! Parse the arguments for msa_pastar
int msa_pastar_options(int argc, char *argv[], std::string &filename, int &threads_num)
{
    return msa_options(Msa_Pastar, argc, argv, filename, threads_num);
}

//! Parse the arguments for msa_astar
int msa_astar_options(int argc, char *argv[], std::string &filename)
{
    int unused;
    return msa_options(Msa_Astar, argc, argv, filename, unused);
}

//! Parse the arguments
int msa_options(int type, int argc, char *argv[], std::string &filename, int &threads_num)
{
    try
    {
        return msa_options_core(type, argc, argv, filename, threads_num);
    }
    catch (boost::program_options::multiple_occurrences &e)
    {
        std::cerr << "Invalid argument: " << e.what() << " from option: " << e.get_option_name() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error\n";
    }
    return -1;
}

/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Parse the arguments options for the msa programs
 */
#include "msa_options.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <boost/version.hpp>

#include "Coord.h"
#include "PAStar.h"

#if BOOST_VERSION<103200
#error "This file requires libboost 1_32 or greater"
#endif

namespace po = boost::program_options;

//! Arguments parse core functions
int msa_options_core(msa_option_type type, int argc, char *argv[], std::string &filename, PAStarOpt &opt)
{
    const std::string description = "Usage " + std::string(argv[0]) + " [OPTIONS] file.fasta";
    std::string hash_read;

    // Arguments Options
    po::options_description common_options("Options");
    common_options.add_options()
        ("version,v", "print version string")
        ("help,h", "produce help message")
        ("memory_debug", "memory debug option") /* Force quit should be used only for debug purposes. Check the struct for
                                   full explanation, it is good to not explain to the users what it does. */
        ;

    // Parallel Options
    po::options_description parallel_options("Parallel Options");
    parallel_options.add_options()
        ("threads,t", po::value<int>(&opt.threads_num)->default_value(opt.threads_num),
         "number of threads")
        ("hash_shift,s", po::value<int>(&opt.hash_shift)->default_value(opt.hash_shift),
         "Hash shift option value")
        ("hash_type,y", po::value<std::string>(&hash_read)->default_value("FZORDER"),
         "Hash type [FZORDER|FSUM|PZORDER|PSUM]")
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
    if (vm.count("hash_type"))
    {
        if (hash_read == "FZORDER")
            opt.hash_type = HashFZorder;
        else if (hash_read == "FSUM")
            opt.hash_type = HashFSum;
        else if (hash_read == "PZORDER")
            opt.hash_type = HashPZorder;
        else if (hash_read == "PSUM")
            opt.hash_type = HashPSum;
        else
            throw msa_options_invalid_value("hash_type");
    }
    if (vm.count("version")) {
        if (type == Msa_Pastar)
            std::cout << "msa_pastar";
        else if (type == Msa_Astar)
            std::cout << "msa_astar";

        std::cout << ", version 1.0\n";
        std::exit(0);
        return 0;
    }
    if (vm.count("help") || !vm.count("file.fasta"))
    {
        std::cout << usage << std::endl;
        return 1;
    }

    boost::filesystem::path fpath(filename);
    if (!boost::filesystem::is_regular_file(fpath))
    {
        std::cout << "File: " << filename << " is not a regular file.\n";
        return 1;
    }

    if (!vm.count("memory_debug"))
        opt.common_options.force_quit = true;
    else
        opt.common_options.force_quit = false;
    return 0;
}

//! Parse the arguments for msa_pastar
int msa_pastar_options(int argc, char *argv[], std::string &filename, PAStarOpt &opt)
{
    return msa_options(Msa_Pastar, argc, argv, filename, opt);
}

//! Parse the arguments for msa_astar
int msa_astar_options(int argc, char *argv[], std::string &filename, AStarOpt &opt)
{
    PAStarOpt pastar_opt;
    int ret;

    ret  = msa_options(Msa_Astar, argc, argv, filename, pastar_opt);
    opt = pastar_opt.common_options;
    return ret;
}

//! Parse the arguments
int msa_options(msa_option_type type, int argc, char *argv[], std::string &filename, PAStarOpt &opt)
{
    try
    {
        return msa_options_core(type, argc, argv, filename, opt);
    }
#if BOOST_VERSION>104100
    catch (boost::program_options::multiple_occurrences &e)
    {
        std::cerr << "Invalid argument: " << e.what() << " from option: " << e.get_option_name() << std::endl;
    }
#endif
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

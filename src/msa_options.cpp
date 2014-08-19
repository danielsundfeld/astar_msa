/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Parse the arguments options for the msa programs
 */
#include <boost/program_options.hpp>

namespace po = boost::program_options;

//! \brief Parse the arguments for the msa programs
int msa_options(int argc, char *argv[], std::string &filename, int &threads_num)
{
    try
    {
        const std::string description = "Usage " + std::string(argv[0]) + " [OPTIONS] file.fasta";

        // Arguments Options
        po::options_description args_options("Options");
        args_options.add_options()
            ("version,v", "print version string")
            ("help,h", "produce help message")
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
        all_options.add(args_options).add(input_fasta_file);

        // The description on how to use
        po::options_description usage(description);
        usage.add(args_options);

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
    catch (boost::program_options::multiple_occurrences &e)
    {
        std::cerr << e.what() << " from option: " << e.get_option_name() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error\n";
    }
    return -1;
}

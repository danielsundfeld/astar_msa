/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef MSA_OPTIONS_H
#define MSA_OPTIONS_H
#include <boost/version.hpp>

#include "Coord.h"
#include "PAStar.h"

enum msa_option_type {
    Msa_Astar,
    Msa_Pastar
};

#if BOOST_VERSION>104100
#define msa_options_invalid_value(X) boost::program_options::validation_error(po::validation_error::invalid_option_value, X)
#else
#define msa_options_invalid_value(X) boost::program_options::validation_error(X)
#endif

int msa_pastar_options(int argc, char *argv[], std::string &filename, PAStarOpt &opt);
int msa_astar_options(int argc, char *argv[], std::string &filename, AStarOpt &opt);
int msa_options(msa_option_type type, int argc, char *argv[], std::string &filename, PAStarOpt &opt);
#endif

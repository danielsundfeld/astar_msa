/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef MSA_OPTIONS_H
#define MSA_OPTIONS_H
#include "Coord.h"
#include "PAStar.h"

enum msa_option_type {
    Msa_Astar,
    Msa_Pastar
};

int msa_pastar_options(int argc, char *argv[], std::string &filename, PAStarOpt &opt);
int msa_astar_options(int argc, char *argv[], std::string &filename);
int msa_options(msa_option_type type, int argc, char *argv[], std::string &filename, PAStarOpt &opt);
#endif

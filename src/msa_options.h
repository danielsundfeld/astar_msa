/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef MSA_OPTIONS_H
#define MSA_OPTIONS_H
#include "Coord.h"

typedef enum _msa_option_type {
    Msa_Astar,
    Msa_Pastar
} msa_option_type;

int msa_pastar_options(int argc, char *argv[], std::string &filename, int &threads_num, int &hash_shift, hashType &hash_type);
int msa_astar_options(int argc, char *argv[], std::string &filename);
int msa_options(int type, int argc, char *argv[], std::string &filename, int &threads_num, int &hash_shift, hashType &hash_type);
#endif

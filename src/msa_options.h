/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#ifndef MSA_OPTIONS_H
#define MSA_OPTIONS_H
typedef enum _msa_option_type {
    Msa_Astar,
    Msa_Pastar
} msa_option_type;

int msa_pastar_options(int argc, char *argv[], std::string &filename, int &threads_num);
int msa_options(int type, int argc, char *argv[], std::string &filename, int &threads_num);
#endif

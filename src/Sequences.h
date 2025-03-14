/*!
 * \class Sequences
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Singleton that holds all sequences being aligned
 */
#ifndef _SEQUENCES_H
#define _SEQUENCES_H
#include <string>
#include <vector>

#include "Coord.h"
#include "Node.h"

class Sequences
{
    public:
        static Sequences* getInstance() { return &instance; };
        void destroyInstance();
        int set_seq(const std::string &x);
        int set_name(const std::string &x);
        static int& get_seq_num() { return n_seq; };
        const std::string& get_seq(int x) const { return seqs.at(x); };
        const std::string& get_seq_name(int x) const { return seqs_name.at(x); };
        template <int N> static Coord<N> get_final_coord();
        template <int N> static Coord<N> get_initial_coord();
        template <int N> static Node<N> get_initial_node();
        template <int N> static bool is_final(const Coord<N> &c);

    private:
        enum seq { MaxSequences = 64 };
        static int n_seq;
        static Sequences instance;
        std::vector<std::string> seqs;
        std::vector<std::string> seqs_name;
        static int final_coord[MaxSequences];

        Sequences();
};
#endif

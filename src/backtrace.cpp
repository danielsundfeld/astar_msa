/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "backtrace.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <map>

#include "Coord.h"
#include "Node.h"
#include "Sequences.h"
#include "TimeCounter.h"

// Decide the best lenght size to print
int get_print_size()
{
    int size = 80;
#ifdef __linux
    struct winsize w;

    // If it is a file, we dont care about lenght
    if (!isatty(1))
        return std::numeric_limits<int>::max();

    // If it is a terminal, get the lenght
    if ((ioctl(0, TIOCGWINSZ, &w) == 0) && (w.ws_col > 1))
        size = w.ws_col - 1;
#endif
    return size;
}

/*!
 * Using the last node on \a ClosedList do a backtrace, verifing
 * gaps, matches and mismatches, saving characteres o the
 * \a backstrace_alignment.
 * The \a ClosedList is an array with size \a map_size
 *
 * At the end of the process, \a alignments contains the
 * answer for every sequence.
 */
template <int N>
void backtrace_create_alignment(std::list<char> *alignments, boost::unordered_map<Coord<N>, Node<N> > *ClosedList, int map_size, int thread_map[])
{
    Sequences *seq = Sequences::getInstance();

    int id = seq->get_final_coord<N>().get_id(map_size, thread_map);
    Node<N> current = ClosedList[id][seq->get_final_coord<N>()];
    std::cout << "Final Score: " << current << std::endl;
    do 
    {
        //std::cout << "Backtrace:\t" << current << std::endl;
        for (int i = 0; i < N; i++)
        {
            char c;
            if (current.pos[i] != current.get_parent()[i])
                c = seq->get_seq(i)[current.pos[i] - 1];
            else
                c = '-';
            alignments[i].push_front(c);
        }
        id = current.get_parent().get_id(map_size, thread_map);
        current = ClosedList[id][current.get_parent()];
    } while (current.pos != Sequences::get_initial_coord<N>());
}

/*!
 * Print the similarity of the sequences in \a alignemnts
 */
template <int N>
void backtrace_print_similarity(std::list<char> *alignments)
{
    // all alignments[i] have same size
    int total = 0;
    int equal = 0;

    std::list<char>::iterator its[N];
    for (int i = 0; i < N; ++i)
        its[i] = alignments[i].begin();

    while (its[0] != alignments[0].end())
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = i + 1; j < N; ++j)
            {
                if (*its[i] == *its[j])
                    ++equal;
                ++total;
            }
        }

        for (int i = 0; i < N; ++i)
            ++its[i];
    }
    float percent = (equal * 100) / (float) total;
    std::cout << "Similarity: "
              << std::fixed << std::setprecision(2)
              << percent << "%" << std::endl;
}

/*!
 * Print the answer in \a alignment. Use a good lenght to print
 * considering the current terminal (linux-only).
 */
template <int N>
void backtrace_print_alignment(std::list<char> *alignments)
{
    int size = get_print_size();

    while (!alignments[0].empty())
    {
        std::cout << std::endl;
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < size; i++)
            {
                if (alignments[j].empty())
                    break;
                std::cout << alignments[j].front();
                alignments[j].pop_front();
            }
            std::cout << std::endl;
        }
    }
}

/*!
 * Print fasta output
 */
template <int N>
void backtrace_print_fasta_file(std::list<char> *alignments, const std::string &output_file)
{
    Sequences *sequences = Sequences::getInstance();

    if (output_file == "")
        return;
    try
    {
        std::ofstream file(output_file);
        for (int j = 0; j < N; j++)
        {
            file << sequences->get_seq_name(j) << std::endl;
            for (const char &ch : alignments[j])
            {
                file << ch;
            }
            file << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Writing file fatal error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error while writing file!\n";
    }
}

/*!
 * MSA-Node backtrace functions prints the answer. Using the
 * \a ClosedList it backtrace every node until the origin is reached
 */
template <int N>
void backtrace(boost::unordered_map< Coord<N>, Node<N> > *ClosedList, const std::string &output_file, int map_size, int thread_map[])
{
    TimeCounter t("Phase 3 - backtrace: ");
    std::list<char> alignments[N];

    backtrace_create_alignment<N>(alignments, ClosedList, map_size, thread_map);
    backtrace_print_similarity<N>(alignments);
    backtrace_print_fasta_file<N>(alignments, output_file);
    backtrace_print_alignment<N>(alignments);
}

#define DECLARE_BACKTRACE_TEMPLATE( X ) \
template void backtrace< X >(boost::unordered_map< Coord< X >, Node< X > >*ClosedList, const std::string &output_file = "", int list_size, int thread_map[] = NULL); \

MAX_NUM_SEQ_HELPER(DECLARE_BACKTRACE_TEMPLATE);

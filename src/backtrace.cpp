/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <sys/ioctl.h>
#include <unistd.h>

#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "Sequences.h"

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
 * \a backstrace_stack.
 * The \a ClosedList is an array with size \a list_size
 *
 * At the end of the process, \a backstrace_stack contains the
 * answer for every sequence.
 */
template <int N>
void backtrace_create_stack(std::stack<char> *backtrace_stack, std::map<Coord<N>, Node<N> > *ClosedList, int list_size)
{
    Sequences *seq = Sequences::getInstance();

    int id = seq->get_final_coord<N>().get_id(list_size);
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
            backtrace_stack[i].push(c);
        }
        id = current.get_parent().get_id(list_size);
        current = ClosedList[id][current.get_parent()];
    } while (current.pos != Sequences::get_initial_coord<N>());
}

/*!
 * Print the answer in \a backstrace_stack. Use a good lenght to print
 * considering the current terminal (linux-only).
 */
template <int N>
void backtrace_print_stack(std::stack<char> *backtrace_stack)
{
    int size = get_print_size();

    while (!backtrace_stack[0].empty())
    {
        std::cout << std::endl;
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < size; i++)
            {
                if (backtrace_stack[j].empty())
                    break;
                std::cout << backtrace_stack[j].top();
                backtrace_stack[j].pop();
            }
            std::cout << std::endl;
        }
    }
}

/*!
 * MSA-Node backtrace functions prints the answer. Using the
 * \a ClosedList it backtrace every node until the origin is reached
 */
template <int N>
void backtrace(std::map< Coord<N>, Node<N> > *ClosedList, int list_size)
{
    std::stack<char> backtrace_stack[N];

    backtrace_create_stack<N>(backtrace_stack, ClosedList, list_size);
    backtrace_print_stack<N>(backtrace_stack);
}

#define DECLARE_BACKTRACE_TEMPLATE( X ) \
template void backtrace< X >(std::map< Coord< X >, Node< X > >*ClosedList, int list_size); \

MAX_NUM_SEQ_TEMPLATE_HELPER(DECLARE_BACKTRACE_TEMPLATE);

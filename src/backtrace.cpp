/*!
 * \filename backtrace.cpp
 * \author Daniel Sundfeld
 */
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <sys/ioctl.h>
#include <unistd.h>

#include "Coord.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

// Decide the best lenght size to print
int get_print_size()
{
    int size = 80;
#ifdef __linux
    struct winsize w;

    // If it is a file, we dont care about lenght
    if (!isatty(1))
        return numeric_limits<int>::max();

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
 *
 * At the end of the process, \a backstrace_stack contains the
 * answer for every sequence.
 */
void backtrace_create_stack(stack<char> *backtrace_stack, std::map<Coord, Node> &ClosedList)
{
    const int dimensions = Sequences::get_seq_num();
    Sequences *seq = Sequences::getInstance();

    Node current = ClosedList[seq->get_final_coord()];
    do 
    {
        //cout << "Backtrace:\t" << current << endl;
        for (int i = 0; i < dimensions; i++)
        {
            char c;
            if (current.pos[i] != current.get_parent()[i])
                c = seq->get_seq(i)[current.pos[i] - 1];
            else
                c = '-';
            backtrace_stack[i].push(c);
        }
        current = ClosedList[current.get_parent()];
    } while (current.pos != current.get_parent());
}

/*!
 * Print the answer in \a backstrace_stack. Use a good lenght to print
 * considering the current terminal (linux-only).
 */
void backtrace_print_stack(stack<char> *backtrace_stack)
{
    const int dimensions = Sequences::get_seq_num();
    int size = get_print_size();

    while (!backtrace_stack[0].empty())
    {
        cout << endl;
        for (int j = 0; j < dimensions; j++)
        {
            for (int i = 0; i < size; i++)
            {
                if (backtrace_stack[j].empty())
                    break;
                cout << backtrace_stack[j].top();
                backtrace_stack[j].pop();
            }
            cout << endl;
        }
    }
}

/*!
 * MSA-Node backtrace functions prints the answer. Using the
 * \a ClosedList it backtrace every node until the origin is reached
 */
void backtrace(std::map<Coord, Node> &ClosedList)
{
    stack<char> *backtrace_stack = new stack<char>[Sequences::get_seq_num()];

    backtrace_create_stack(backtrace_stack, ClosedList);
    backtrace_print_stack(backtrace_stack);
    delete[] backtrace_stack;
}

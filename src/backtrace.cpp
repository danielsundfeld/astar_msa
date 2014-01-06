/*!
 * \filename backtrace.cpp
 * \author Daniel Sundfeld
 */
#include <iostream>
#include <map>
#include <stack>
#include <sys/ioctl.h>

#include "Coord.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

// Decide the best size to print on current terminal
int get_terminal_size()
{
    int size = 80;
#ifdef __linux
    // This method works with resized terminal
    struct winsize w;

    if ((ioctl(0, TIOCGWINSZ, &w) == 0) && (w.ws_col > 1))
        size = w.ws_col - 1;
#endif
    return size;
}

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

void backtrace_print_stack(stack<char> *backtrace_stack)
{
    const int dimensions = Sequences::get_seq_num();
    int size = get_terminal_size();

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

void backtrace(std::map<Coord, Node> &ClosedList)
{
    stack<char> *backtrace_stack = new stack<char>[Sequences::get_seq_num()];

    backtrace_create_stack(backtrace_stack, ClosedList);
    backtrace_print_stack(backtrace_stack);
    delete[] backtrace_stack;
}


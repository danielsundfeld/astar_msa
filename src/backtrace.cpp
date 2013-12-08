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
#ifdef linux
    // This method works with resized terminal
    struct winsize w;

    if ((ioctl(0, TIOCGWINSZ, &w) == 0) && (w.ws_col > 1))
        size = w.ws_col - 1;
#endif
    return size;
}

void backtrace_create_stack(stack<char> *backtrace_stack, std::map<Coord, Node> &ClosedList)
{
    Sequences *seq = Sequences::getInstance();

    Node current = ClosedList[seq->get_final_coord()];
    do 
    {
        char c;
        //cout << "Backtrace:\t" << current << endl;
        if (current.pos.get_x() != current.get_parent().get_x())
            c = seq->get_seq(0)[current.pos.get_x() - 1];
        else
            c = '-';
        backtrace_stack[0].push(c);

        if (current.pos.get_y() != current.get_parent().get_y())
            c = seq->get_seq(1)[current.pos.get_y() - 1];
        else
            c = '-';
        backtrace_stack[1].push(c);

        if (current.pos.get_z() != current.get_parent().get_z())
            c = seq->get_seq(2)[current.pos.get_z() - 1];
        else
            c = '-';
        backtrace_stack[2].push(c);

        current = ClosedList[current.get_parent()];
    } while (!(current.pos == current.get_parent()));
}

void backtrace_print_stack(stack<char> *backtrace_stack)
{
    int dimensions = Sequences::getInstance()->get_seq_num();
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
    stack<char> backtrace_stack[3];

    backtrace_create_stack(backtrace_stack, ClosedList);
    backtrace_print_stack(backtrace_stack);
}


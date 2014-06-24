#include <iostream>
#include <limits>
#include <map>

#include "backtrace.h"
#include "Coord.h"
#include "HeuristicHPair.h"
#include "Node.h"
#include "Sequences.h"
#include "PriorityList.h"
#include "PriorityTypes.h"

using namespace std;

string s1 = "WWWWWWWWWW";

#define N_SEQ 4
void load_sequences()
{
    cout << "Loading Sequences...\n";
    Sequences *seq = Sequences::getInstance();

    for (int i = 0; i < N_SEQ; ++i)
        seq->set_seq(s1);

    HeuristicHPair::getInstance()->init();
    cout << "done!\n";
}

void quick_test_list()
{
    cout << "Starting queue/dequeue/test... ";
    PriorityList<N_SEQ> OpenList;
    Coord<N_SEQ> c2;
    for (int i = 0; i < N_SEQ; ++i)
        c2[i] = 1;
    Node<N_SEQ> n2(15, c2, (1 << N_SEQ) - 1);
    OpenList.enqueue(n2);

    Coord<N_SEQ> c3;
    for (int i = 0; i < N_SEQ; ++i)
        c3[i] = 3;
    Node<N_SEQ> n3(7, c3, (1 << N_SEQ) - 1);
    OpenList.enqueue(n3);

    Node<N_SEQ> n1(0, Coord<N_SEQ>(), (1 << N_SEQ) - 1);
    OpenList.enqueue(n1);

    Node<N_SEQ> n;
    if (OpenList.dequeue(n) == false || n != n1)
    {
        cout << "Bug at 1sr dequeue...\n";
        return;
    }
    if (OpenList.dequeue(n) == false || n != n3)
    {
        cout << "Bug at 2nd dequeue...\n";
        return;
    }
    if (OpenList.dequeue(n) == false || n != n2)
    {
        cout << "Bug at 3rd dequeue...\n";
        return;
    }
    if (OpenList.dequeue(n) == true)
    {
        cout << "Bug at 4th dequeue...\n";
        return;
    }

    Node<N_SEQ> n4(20, c2, (1 << N_SEQ) - 1);
    Node<N_SEQ> n5(15, c2, (1 << N_SEQ) - 1);
    Node<N_SEQ> n6(30, c2, (1 << N_SEQ) - 1);
    OpenList.conditional_enqueue(n4);
    OpenList.conditional_enqueue(n5);
    OpenList.conditional_enqueue(n6);
    if (OpenList.get_highest_priority() != 15)
    {
        cout << "Bug at conditional enqueue or highest priority\n";
        return;
    }
    if (OpenList.dequeue(n) == false || !(n != n4) || n != n5 || !(n != n6))
    {
        cout << "Bug at conditional enqueue or 5th dequeue\n";
        return;
    }
    if (OpenList.dequeue(n) == true)
    {
        cout << "Bug at 6th dequeue...\n";
        return;
    }
    cout << "done!\n";
    return;
}

int main(void)
{
    load_sequences();
    quick_test_list();

    return 0;
}

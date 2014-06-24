#include <iostream>
#include <limits>
#include <map>

#include "backtrace.h"
#include "Coord.h"
#include "HeuristicHPair.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

string s1 = "WWWWWWWWWW";
#define N_SEQ 4
void load_sequences()
{
    cout << "Testing Sequences... " << flush;
    Sequences *seq = Sequences::getInstance();

    for (int i = 0; i < N_SEQ; ++i)
        seq->set_seq(s1);

    for (unsigned int i = 0; i < Sequences::get_seq_num(); ++i)
        if (seq->get_seq(i) != s1)
            cout << "Bug at Sequences::get_seq/set_seq or get_seq_num\n";

    Coord<N_SEQ> initial = seq->get_initial_coord<N_SEQ>();
    for (int i = 0; i < N_SEQ; ++i)
        if (initial[i] != 0)
            cout << "Bug at Sequences::get_initial_coord\n";

    Coord<N_SEQ> c = seq->get_final_coord<N_SEQ>();
    if (seq->is_final(c) != true)
        cout << "Bug at Sequences::get_final_coord/is_final\n";

    cout << "done!\n";
}

void test_heuristic()
{
    Sequences *seq = Sequences::getInstance();
    cout << "Testing Heuristic:\n" << flush;
    HeuristicHPair::getInstance()->init();

    Node <N_SEQ> c = seq->get_initial_node<N_SEQ>();
    if (c.get_f() != 0 || c.get_g() != 0)
        cout << "Bug at HeuristicHPair::calculate_h/Sequence::get_initial_node\n";

    cout << "Testing Heursitic done!\n";
}

void test_ostream()
{
    const Node<3> n1;

    cout << "Testing ostream<< operator...\n" << n1 << "\ndone!\n";
}

void test_constructor()
{
    Coord<4> c;
    c[0] = 1;
    c[1] = 1;
    c[2] = 1;
    c[3] = 1;
    const Node<4> n(10, c, 1 << 4);
    Node<4> n2;

    cout << "Testing constructor...";
    if (n.get_g() != 10)
        cout << "Bug at constructor/get_g\n";
    cout << "done!\n";
}

void test_node()
{
    cout << "Testing node_ops...";
    Node<N_SEQ> n2;
    n2.set_max();
    if (n2.get_g() != std::numeric_limits<int>::max())
        cout << "Bug at max.\n";

    Node<N_SEQ> n = Sequences::get_initial_node<N_SEQ>();
    if (n.pos != Sequences::get_initial_coord<N_SEQ>())
        cout << "Bug at Sequences::initial_node/pos\n";

    vector< Node<N_SEQ> > vector_node;
    n.getNeigh(&vector_node);

    for (vector< Node<N_SEQ> >::iterator it = vector_node.begin(); it != vector_node.end(); ++it)
        if (it->get_parent() != n.pos)
            cout << "Bug at get_neigh/get_parent\n";

    cout << "done!\n";
}

void test_backtrace(bool add_dumb = false)
{
    Node<N_SEQ> n = Sequences::get_initial_node<N_SEQ>();
    std::map< Coord<N_SEQ>, Node<N_SEQ> > ClosedList;

    ClosedList[n.pos] = n;
    if (add_dumb)
    {
        vector< Node<N_SEQ> > v;
        n.getNeigh(&v);
        n = v[0];
        ClosedList[n.pos] = n;
    }

    while (!(Sequences::is_final(n.pos)))
    {
        vector< Node<N_SEQ> > v;
        n.getNeigh(&v);

        Node<N_SEQ> min;
        min.set_max();

        for (auto &it : v)
            if (min.get_f() > it.get_f())
                min = it;

        n = min;
        ClosedList[n.pos] = n;
    }
    backtrace(&ClosedList);
}

void test_all_backtrace()
{
    test_backtrace(true);
    test_backtrace(false);
}

int main(void)
{
    load_sequences();
    test_heuristic();
    test_ostream();
    test_constructor();
    test_node();
    test_all_backtrace();

    return 0;
}

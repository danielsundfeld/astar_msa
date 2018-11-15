#include <iostream>
#include <map>

#include "backtrace.h"
#include "HeuristicHPair.h"
#include "read_fasta.h"

using namespace std;

#define N_SEQ 4

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
    if (read_fasta_file("arq.fasta"))
	 {
        cout << "Error loading fasta arq.fasta\n";
		  return -1;
    }
	 if (Sequences::get_seq_num() != N_SEQ)
    {
        cout << "Invalid number of sequences in arq.fasta. Expected: " << N_SEQ << endl;
		  return -1;
    }
    HeuristicHPair::getInstance()->init();
    test_all_backtrace();
    return 0;
}

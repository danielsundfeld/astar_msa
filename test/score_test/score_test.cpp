#include <algorithm>
#include <iostream>

#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "HeuristicHPair.h"
#include "Sequences.h"

using namespace std;

Node current;
map<Coord, Node> ClosedList;

void add_to_closed_list(Node &father, const Coord &son, std::map<Coord, Node> &ClosedList)
{
    vector<Node> neigh;

    father.getNeigh(&neigh);

    for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        if ((*it).pos == son)
        {
            ClosedList[it->pos] = *it;
            father = *it;
            return;
        }
}

void test_init(vector< string > &a)
{
    Sequences *seq = Sequences::getInstance();

    // Remove gaps from the strings
    for (auto it = a.begin(); it != a.end(); it++)
    {
        string s1 = *it;
        s1.erase(remove(s1.begin(), s1.end(), '-'),
                           s1.end());
        seq->set_seq(s1);
    }

    HeuristicHPair::getInstance()->init();
    Coord c = Sequences::get_initial_coord();
    const Node node_zero = Sequences::get_initial_node();
    ClosedList[node_zero.pos] = node_zero;
    current = node_zero;
}

void test_end(vector< string > &a)
{
    cout << "Final score:\t" << ClosedList[Sequences::get_final_coord()] << endl;

    cout << "Compare answers:" << endl;
    cout << "#####Original#####" << endl;
    for (auto it = a.begin(); it != a.end(); ++it)
        cout << *it << endl;
    cout << "#####Backtraced#####";
    backtrace(&ClosedList);
    Sequences::destroyInstance();
    HeuristicHPair::destroyInstance();
    ClosedList.clear();
    cout << "#####Test end!#####\n\n";
}

void sanity_check(vector< string > &a)
{
    auto it = a.begin();
    size_t len = it->length();
    ++it;

    for (; it != a.end(); it++)
        if (it->length() != len)
        {
            cout << "Strings MUST have the same size. Please fix this string:\n" << *it << endl;
            exit(1);
        }
    return;
}

void run_test(vector< string > &a)
{
    Coord c(Sequences::get_seq_num());
    current = Sequences::get_initial_node();

    int column = 0;
    while (c != Sequences::get_final_coord())
    {
        int dimension = 0;
        for (auto it = a.begin(); it != a.end(); it++, dimension++)
        {
            if((*it)[column] != '-')
                c[dimension] += 1;
        }
        //cout << c << endl;
        column++;
        add_to_closed_list(current, c, ClosedList);
    }
}

void run_all(vector< string > &a)
{
    test_init(a);
    sanity_check(a);
    run_test(a);
    test_end(a);
}

int run_test1(void)
{
    vector< string > a;
    a.push_back("--MSLIVTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("--MSLIVTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("--MEKIRTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("HPSLPVRTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("PQAAKVRVWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("------MLWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");

    run_all(a);
    return 0;
}

int run_test2(void)
{
    vector< string > a;
    a.push_back("---MSLIVTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("---MSLIVTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("---MEKIRTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("HP-SLPVRTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("-PQAAKVRVWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    a.push_back("-------MLWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");

    run_all(a);
    return 0;
}

int main(void)
{
    run_test1();
    run_test2();
    return 0;
}

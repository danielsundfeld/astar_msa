#include <iostream>

#include "backtrace.h"
#include "Coord.h"
#include "Node.h"
#include "HeuristicHPair.h"
#include "Sequences.h"

using namespace std;

void add_to_closed_list(Node &father, const Coord &son, std::map<Coord, Node> &ClosedList)
{
    vector<Node> neigh;

    father.getNeigh(neigh);

    for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        if ((*it).pos == son)
        {
            ClosedList[it->pos] = *it;
            father = *it;
            return;
        }
}

Node current;
map<Coord, Node> ClosedList;

void test_init()
{
    HeuristicHPair::getInstance()->init();
    Coord c = Sequences::get_initial_coord();
    const Node node_zero = Sequences::get_initial_node();
    ClosedList[node_zero.pos] = node_zero;
    current = node_zero;
}

void test_end()
{
    cout << "Final score:\t" << ClosedList[Sequences::get_final_coord()] << endl;
    backtrace(ClosedList);
    Sequences::destroyInstance();
    HeuristicHPair::destroyInstance();
    ClosedList.clear();
}

int run_test1(void)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("WWW");
    seq->set_seq("WW");
    seq->set_seq("WWW");

    test_init();
    add_to_closed_list(current, Coord(0, 0, 1), ClosedList);
    add_to_closed_list(current, Coord(1, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 3), ClosedList);
    add_to_closed_list(current, Coord(3, 2, 3), ClosedList);
    test_end();
    return 0;
}

int run_test2(void)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("WWW");
    seq->set_seq("WW");
    seq->set_seq("WW");

    test_init();
    add_to_closed_list(current, Coord(0, 0, 1), ClosedList);
    add_to_closed_list(current, Coord(1, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(3, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(3, 2, 2), ClosedList);
    test_end();
    return 0;
}

int run_test3(void)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("WW");
    seq->set_seq("WWW");
    seq->set_seq("WW");

    test_init();
    add_to_closed_list(current, Coord(0, 0, 1), ClosedList);
    add_to_closed_list(current, Coord(1, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 3, 2), ClosedList);
    test_end();
    return 0;
}

int run_test4(void)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("WW");
    seq->set_seq("WWWW");
    seq->set_seq("WW");

    test_init();
    add_to_closed_list(current, Coord(0, 0, 1), ClosedList);
    add_to_closed_list(current, Coord(1, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 3, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 4, 2), ClosedList);
    test_end();
    return 0;
}

int run_test5(void)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("WW");
    seq->set_seq("WW");
    seq->set_seq("WWWW");

    test_init();
    add_to_closed_list(current, Coord(0, 0, 1), ClosedList);
    add_to_closed_list(current, Coord(1, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 3), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 4), ClosedList);
    test_end();
    return 0;
}

int run_test6(void)
{
    Sequences *seq = Sequences::getInstance();
    seq->set_seq("WWWW");
    seq->set_seq("WW");
    seq->set_seq("WW");

    test_init();
    add_to_closed_list(current, Coord(0, 0, 1), ClosedList);
    add_to_closed_list(current, Coord(1, 1, 2), ClosedList);
    add_to_closed_list(current, Coord(2, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(3, 2, 2), ClosedList);
    add_to_closed_list(current, Coord(4, 2, 2), ClosedList);
    test_end();
    return 0;
}

int main(void)
{
    run_test1();
    run_test2();
    run_test3();
    run_test4();
    run_test5();
    run_test6();
    return 0;
}

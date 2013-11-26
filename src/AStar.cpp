#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <stdio.h>

#include "Coord.h"
#include "Node.h"
#include "Sequences.h"

using namespace std;

string a = "AAAAAAA";
string b = "AAABAAA";
string c = "AAACAAA";

void print_coord(const char msg[], Node l)
{
    printf("%s (%d) (%d %d %d)\n", msg, l.get_g(), l.pos.get_x(), l.pos.get_y(), l.pos.get_z());
}

int a_star()
{
    map<Coord, Node> OpenList;
    map<Coord, Node> ClosedList;
    priority_queue<Node, vector<Node>, PriorityNode> pq;
    Sequences *seq = Sequences::getInstance();
    seq->set_seq(a);
    seq->set_seq(b);
    seq->set_seq(c);

    pq.push(Node(0, Coord(0, 0, 0))); //Zero cost, zero coords.
    Node current = pq.top();
    while (!pq.empty() && seq->is_not_final(current.pos))
    {
        print_coord("Visitando no", current);
        pq.pop();
        ClosedList[current.pos] = current;

        vector<Node> neigh = current.getNeigh();
        for (vector<Node>::iterator it = neigh.begin() ; it != neigh.end(); ++it)
        {
            pq.push(*it);
        }
        current = pq.top();
    }
    print_coord("Score final:", current);
    return 0;
}

/*
OPEN = priority queue containing START
CLOSED = empty set
while lowest rank in OPEN is not the GOAL:
  current = remove lowest rank item from OPEN
  add current to CLOSED
  for neighbors of current:
    cost = g(current) + movementcost(current, neighbor)
    if neighbor in OPEN and cost less than g(neighbor):
      remove neighbor from OPEN, because new path is better
    if neighbor in CLOSED and cost less than g(neighbor): **
      remove neighbor from CLOSED
    if neighbor not in OPEN and neighbor not in CLOSED:
      set g(neighbor) to cost
      add neighbor to OPEN
      set priority queue rank to g(neighbor) + h(neighbor)
      set neighbor's parent to current

*/

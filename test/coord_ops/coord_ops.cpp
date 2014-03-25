#include <iostream>
#include <map>
#include <queue>
#include "Coord.h"
#include "Node.h"

using namespace std;

int main(void)
{
    Coord c1(0, 1, 2);
    Coord c3(0, 1, 2);
    Coord c2;

    cout << "sizeof(Node): " << sizeof(Node) << endl;
    cout << "sizeof(Coord): " << sizeof(Coord) << endl;
    if (c1 == c3)
        cout << "c1 == c3\n";
    else
        cout << "c1 != c3\n";
    cout << "c1: " << c1[0] << " " << c1[1] << " " << c1[2] << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;
 
    cout << "c1 (before append): " << c1 << endl;
    c1.append(3);
    cout << "c1: " << c1[0] << " " << c1[1] << " " << c1[2] << " " << c1[3] << endl;

    cout << "c1 (after append): " << c1 << endl;

    Coord c4(3, 1);

    for (int i = 0; i < 8; i++)
        cout << "son: " << i << " " << c4.neigh(i) << " sum : " << c4.neigh(i).get_sum() << endl;
//    for (int i = 1; i < 8; i++)
//        cout << "father: " << i << " " << c4.parent(i) << endl;
    cout << "final: " << c4 << endl;

    cout << "c1: " << c1 << endl;
    cout << "c1_sum: " << c1.get_sum() << endl;
    cout << "c4: " << c4 << endl;
    cout << "c4_sum: " << c4.get_sum() << endl;
    Coord c5 = c4.neigh(3);
    cout << "c5: " << c5 << endl;
    cout << "c5_sum: " << c5.get_sum() << endl;
    return 0;
}


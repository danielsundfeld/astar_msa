#include <iostream>
#include "Coord.h"

using namespace std;

void test_ostream()
{
    const Coord<3> c1;
    Coord<3> c2(1);

    cout << "Testing ostream<< operator...\n" << c1 << "/" << c2 << "\ndone!\n";
}

void test_brackets()
{
    const Coord<3> c1;
    Coord<3> c2(1);

    cout << "Testing default constructor, [] and const [] operators...\n";
    for (int i = 0; i < 3; ++i)
    {
        if (c1[i] == c2[i])
            cout << "Bug at: " << c2 << "/" << c1 << ". c1[i] == c2[i], where i=" << i << endl;
    }

    for (int i = 0; i < 3; ++i)
    {
        c2[i] = 0;
        if (c1[i] != c2[i])
            cout << "Bug at: " << c2 << "/" << c1 << ". c1[i] != c2[i], where i=" << i << endl;
    }
    cout << "done!\n";
}

void test_equal()
{
    const Coord<3> c1(0);
    Coord<3> c2(0);

    cout << "Testing != and == operators...\n";
    if (!(c2 == c1))
        cout << "Bug at: !(" << c2 << "==" << c1 << ")" << endl;
    if (c2 != c1)
        cout << "Bug at: " << c2 << "!=" << c1 << endl;

    c2[0] = 0;
    c2[1] = 1;
    c2[2] = 0;
    for (int k = 0; k <= 1; ++k)
    {
        c2[2] = k;

        if (c2 == c1)
            cout << "Bug at: " << c2 << "==" << c1 << endl;
        if (!(c2 != c1))
            cout << "Bug at: !(" << c2 << "!=" << c1 << ")" << endl;
    }

    c2[0] = 0;
    c2[1] = 0;
    c2[2] = 1;
    for (int k = 0; k <= 1; ++k)
    {
        c2[1] = k;

        if (c2 == c1)
            cout << "Bug at: " << c2 << "==" << c1 << endl;
        if (!(c2 != c1))
            cout << "Bug at: !(" << c2 << "!=" << c1 << ")" << endl;
    }

    c2[0] = 1;
    c2[1] = 0;
    c2[2] = 0;
    for (int j = 0; j <= 1; ++j)
        for (int k = 0; k <= 1; ++k)
        {
            c2[1] = j;
            c2[2] = k;

            if (c2 == c1)
                cout << "Bug at: " << c2 << "==" << c1 << endl;
            if (!(c2 != c1))
                cout << "Bug at: !(" << c2 << "!=" << c1 << ")" << endl;
        }
    cout << "done!\n";
}

void test_assignment()
{
    Coord<3> c1(10);
    Coord<3> c2(20);

    cout << "Testing assignment operations...\n";
    c1 = c1;
    c2 = c1;

    if (c2 != c1)
        cout << "Bug at: " << c2 << "!=" << c1 << endl;

    cout << "done!\n";
}

template <int N>
void test_father_and_son(int k, const Coord<N> &father, const Coord<N> &son)
{
    if (father.neigh(k) != son)
        cout << "Bug at: " << son << " not neigh(" << k << ") " << father << endl;
    if (son.parent(k) != father)
        cout << "Bug at: " << father << " not parent(" << k << ") " << son << endl;
}

void test_neigh_and_parent()
{
    const Coord<3> father(2);
    Coord<3> son;

    cout << "Testing father/son operations...\n";
    son[0] = 3;
    son[1] = 2;
    son[2] = 2;
    test_father_and_son(1, father, son);

    son[0] = 2;
    son[1] = 3;
    son[2] = 2;
    test_father_and_son(2, father, son);

    son[0] = 3;
    son[1] = 3;
    son[2] = 2;
    test_father_and_son(3, father, son);

    son[0] = 2;
    son[1] = 2;
    son[2] = 3;
    test_father_and_son(4, father, son);

    son[0] = 3;
    son[1] = 2;
    son[2] = 3;
    test_father_and_son(5, father, son);

    son[0] = 2;
    son[1] = 3;
    son[2] = 3;
    test_father_and_son(6, father, son);

    son[0] = 3;
    son[1] = 3;
    son[2] = 3;
    test_father_and_son(7, father, son);

    cout << "done!\n";
}

#define THREADS 4
#define DIM 4
// Test all bits with DIM dimensions
void test_all_bit_hash_zorder()
{
    cout << "Testing all bits of hashes with " << DIM << "-dimensions...\n";
    unsigned int hash_not_zero = 1;
    for (unsigned int i = 1; hash_not_zero; i <<= 1)
    {
        for (unsigned int j = 0; j < DIM && hash_not_zero; ++j)
        {
            Coord<DIM> c;
            c[j] = i;

            hash_not_zero = c.get_z_order_curve();
            cout << "Coordinate:" << c << " curve: " << hash_not_zero << " (" << c.z_order_hash_slow<HASH_SHIFT>(THREADS) << '/' << c.z_order_hash<HASH_SHIFT>(THREADS) << ')' << endl;
            if (c.z_order_hash_slow<HASH_SHIFT>(THREADS) != c.z_order_hash<HASH_SHIFT>(THREADS))
            {
                cout << "Bug at zorder_hash: " << c << endl;
                cout << "Slow: " << c.z_order_hash_slow<HASH_SHIFT>(THREADS) << endl;
                cout << "Fast: " << c.z_order_hash<HASH_SHIFT>(THREADS) << endl;
                cout << endl;
            }
        }
    }
    cout << "done!\n\n";
}

int main(void)
{
    test_ostream();
    test_brackets();
    test_equal();
    test_assignment();
    test_neigh_and_parent();
    test_all_bit_hash_zorder();

    return 0;
}

#include <iostream>

#include "Coord.h"

using namespace std;

#define THREADS 4

// Test all Coords from 0 to 256 and 4 dimensions
void big_test4()
{
    for (int i = 0; i < 256; ++i)
    {
        cout << i << endl;
        for (int j = 0; j < 256; ++j)
        {
            for (int k = 0; k < 256; ++k)
            {
                for (int l = 0; l < 256; ++l)
                {
                    Coord c(4);

                    c[0] = i;
                    c[1] = j;
                    c[2] = k;
                    c[3] = l;

                    if (c.z_order_hash_slow(THREADS) != c.z_order_hash(THREADS))
                    {
                        cout << "Bug at zorder_hash: " << c << endl;
                        cout << "Slow: " << c.z_order_hash_slow(THREADS) << endl;
                        cout << "Fast: " << c.z_order_hash(THREADS) << endl;
                        cout << endl;
                    }
                }
            }
        }
    }
}

// Test all Coords from 0 to 256 and 3 dimensions
void big_test3()
{
    for (int i = 0; i < 256; ++i)
    {
        cout << i << endl;
        for (int j = 0; j < 256; ++j)
        {
            for (int k = 0; k < 256; ++k)
            {
                Coord c(3);

                c[0] = i;
                c[1] = j;
                c[2] = k;

                if (c.z_order_hash_slow(THREADS) != c.z_order_hash(THREADS))
                {
                    cout << "Bug at zorder_hash: " << c << endl;
                    cout << "Slow: " << c.z_order_hash_slow(THREADS) << endl;
                    cout << "Fast: " << c.z_order_hash(THREADS) << endl;
                    cout << endl;
                }
            }
        }
    }
}

#define DIM 4
// Test all bits with DIM dimensions
void all_bit()
{
    cout << "Testing all bits of hashes with " << DIM << "-dimensions:\n";
    unsigned int hash_not_zero = 1;
    for (unsigned int i = 1; hash_not_zero; i <<= 1)
    {
        for (unsigned int j = 0; j < DIM && hash_not_zero; ++j)
        {
            Coord c(DIM);
            c[j] = i;

            hash_not_zero = c.get_z_order_curve();
            cout << "Coordinate:" << c << " curve: " << hash_not_zero << " (" << c.z_order_hash_slow(THREADS) << '/' << c.z_order_hash(THREADS) << ')' << endl;
            if (c.z_order_hash_slow(THREADS) != c.z_order_hash(THREADS))
            {
                cout << "Bug at zorder_hash: " << c << endl;
                cout << "Slow: " << c.z_order_hash_slow(THREADS) << endl;
                cout << "Fast: " << c.z_order_hash(THREADS) << endl;
                cout << endl;
            }
        }
    }
    cout << "done!\n\n";
}

// Somewhere to place some easy and quick tests
void minor_test()
{
    Coord c_zero(DIM);
    cout << c_zero << "/" << c_zero.get_z_order_curve() << " " << c_zero.z_order_hash(4) << ' ' << c_zero.z_order_hash_slow(4) << endl;

    Coord c(DIM);
    c[0] = 0xFFFFFF;
    c[1] = 3;
    cout << c.z_order_hash_slow(THREADS) << " " << c.z_order_hash(THREADS) << " " << c.part_z_order_hash(THREADS) << endl;

    c[2] = 0xFFFFFF;
    c[3] = 0xFFFFFF;
    cout << c.z_order_hash_slow(THREADS) << " " << c.z_order_hash(THREADS) << " " << c.part_z_order_hash(THREADS) << endl;
}

int main(void)
{
    all_bit();
    minor_test();
    //big_test4();
    //big_test3();
    return 0;
}

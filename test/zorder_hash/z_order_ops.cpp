#include <iostream>

#include "Coord.h"

using namespace std;

#define THREADS 4

// Test with more complicated code, fixed dimensions: 4
void big_test()
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

#define DIM 4
int main(void)
{
    Coord c_zero(DIM);
    cout << c_zero << "/" << c_zero.get_z_order_curve() << endl;
    
    unsigned int hash_not_zero = 1;
    for (unsigned int i = 1; hash_not_zero; i <<= 1)
    {
        for (unsigned int j = 0; j < DIM && hash_not_zero; ++j)
        {
    		Coord c(DIM);
            c[j] = i;

            hash_not_zero = c.get_z_order_curve();
            cout << c << "/" << hash_not_zero << ' ' << c.z_order_hash_slow(THREADS) << '/' << c.z_order_hash(THREADS) << endl;
            if (c.z_order_hash_slow(THREADS) != c.z_order_hash(THREADS))
            {
                cout << "Bug at zorder_hash: " << c << endl;
            }
        }
    }
    //big_test();
    Coord c(DIM);
    c[2] = 2;
    c[3] = 128;
    cout << c.z_order_hash_slow(THREADS) << " " << c.z_order_hash(THREADS) << endl;
    return 0;
}

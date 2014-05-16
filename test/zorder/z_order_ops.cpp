#include <iostream>

#include "Coord.h"

using namespace std;

#define DIM 4

int main(void)
{
    Coord c;

    for (int i = 0; i < DIM; ++i)
        c.append(0);

    cout << c << "/" << c.get_z_order_curve() << endl;
    
    unsigned int hash_not_zero = 1;

    for (unsigned int i = 1; hash_not_zero; i <<= 1)
    {
        for (unsigned int j = 0; j < DIM && hash_not_zero; ++j)
        {
            c.clear();
            for (int i = 0; i < DIM; ++i)
                c.append(0);
            c[j] = i;

            hash_not_zero = c.get_z_order_curve();
            cout << c << "/" << hash_not_zero << endl;
        }
    }
    return 0;
}

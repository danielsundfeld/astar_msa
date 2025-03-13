#include <iostream>
#include <iomanip>

#include "Cost.h"

using namespace std;

char order[] = { 'C', 'S', 'T', 'P', 'A', 'G', 'N', 'D', 'E', 'Q', 'H', 'R', 'K', 'M', 'I', 'L', 'V', 'F', 'Y', 'W' };

int localpam['Z']['Z'];

void initpam(void)
{
    localpam['W']['W'] = 0;
    localpam['W']['C'] = localpam['C']['W'] = 25;
    localpam['W']['S'] = localpam['S']['W'] = 19;
    localpam['W']['T'] = localpam['T']['W'] = 22;
    localpam['W']['P'] = localpam['P']['W'] = 23;
    localpam['W']['A'] = localpam['A']['W'] = 23;
    localpam['W']['G'] = localpam['G']['W'] = 24;
    localpam['W']['N'] = localpam['N']['W'] = 21;
    localpam['W']['D'] = localpam['D']['W'] = 24;
    localpam['W']['E'] = localpam['E']['W'] = 24;
    localpam['W']['Q'] = localpam['Q']['W'] = 22;
    localpam['W']['H'] = localpam['H']['W'] = 20;
    localpam['W']['R'] = localpam['R']['W'] = 15;
    localpam['W']['K'] = localpam['K']['W'] = 20;
    localpam['W']['M'] = localpam['M']['W'] = 21;
    localpam['W']['I'] = localpam['I']['W'] = 22;
    localpam['W']['L'] = localpam['L']['W'] = 19;
    localpam['W']['V'] = localpam['V']['W'] = 23;
    localpam['W']['F'] = localpam['F']['W'] = 17;
    localpam['W']['Y'] = localpam['Y']['W'] = 17;

    localpam['Y']['Y'] = 7;
    localpam['Y']['C'] = localpam['C']['Y'] = 17;
    localpam['Y']['S'] = localpam['S']['Y'] = 20;
    localpam['Y']['T'] = localpam['T']['Y'] = 20;
    localpam['Y']['P'] = localpam['P']['Y'] = 22;
    localpam['Y']['A'] = localpam['A']['Y'] = 20;
    localpam['Y']['G'] = localpam['G']['Y'] = 22;
    localpam['Y']['N'] = localpam['N']['Y'] = 19;
    localpam['Y']['D'] = localpam['D']['Y'] = 21;
    localpam['Y']['E'] = localpam['E']['Y'] = 21;
    localpam['Y']['Q'] = localpam['Q']['Y'] = 21;
    localpam['Y']['H'] = localpam['H']['Y'] = 17;
    localpam['Y']['R'] = localpam['R']['Y'] = 21;
    localpam['Y']['K'] = localpam['K']['Y'] = 21;
    localpam['Y']['M'] = localpam['M']['Y'] = 19;
    localpam['Y']['I'] = localpam['I']['Y'] = 18;
    localpam['Y']['L'] = localpam['L']['Y'] = 18;
    localpam['Y']['V'] = localpam['V']['Y'] = 19;
    localpam['Y']['F'] = localpam['F']['Y'] = 10;

    localpam['F']['F'] = 8;
    localpam['F']['C'] = localpam['C']['F'] = 21;
    localpam['F']['S'] = localpam['S']['F'] = 20;
    localpam['F']['T'] = localpam['T']['F'] = 20;
    localpam['F']['P'] = localpam['P']['F'] = 22;
    localpam['F']['A'] = localpam['A']['F'] = 21;
    localpam['F']['G'] = localpam['G']['F'] = 22;
    localpam['F']['N'] = localpam['N']['F'] = 21;
    localpam['F']['D'] = localpam['D']['F'] = 23;
    localpam['F']['E'] = localpam['E']['F'] = 22;
    localpam['F']['Q'] = localpam['Q']['F'] = 22;
    localpam['F']['H'] = localpam['H']['F'] = 19;
    localpam['F']['R'] = localpam['R']['F'] = 21;
    localpam['F']['K'] = localpam['K']['F'] = 22;
    localpam['F']['M'] = localpam['M']['F'] = 17;
    localpam['F']['I'] = localpam['I']['F'] = 16;
    localpam['F']['L'] = localpam['L']['F'] = 15;
    localpam['F']['V'] = localpam['V']['F'] = 18;

    localpam['V']['V'] = 13;
    localpam['V']['C'] = localpam['C']['V'] = 19;
    localpam['V']['S'] = localpam['S']['V'] = 18;
    localpam['V']['T'] = localpam['T']['V'] = 17;
    localpam['V']['P'] = localpam['P']['V'] = 18;
    localpam['V']['A'] = localpam['A']['V'] = 17;
    localpam['V']['G'] = localpam['G']['V'] = 18;
    localpam['V']['N'] = localpam['N']['V'] = 19;
    localpam['V']['D'] = localpam['D']['V'] = 19;
    localpam['V']['E'] = localpam['E']['V'] = 19;
    localpam['V']['Q'] = localpam['Q']['V'] = 19;
    localpam['V']['H'] = localpam['H']['V'] = 19;
    localpam['V']['R'] = localpam['R']['V'] = 19;
    localpam['V']['K'] = localpam['K']['V'] = 19;
    localpam['V']['M'] = localpam['M']['V'] = 15;
    localpam['V']['I'] = localpam['I']['V'] = 13;
    localpam['V']['L'] = localpam['L']['V'] = 15;

    localpam['L']['L'] = 11;
    localpam['L']['C'] = localpam['C']['L'] = 23;
    localpam['L']['S'] = localpam['S']['L'] = 20;
    localpam['L']['T'] = localpam['T']['L'] = 19;
    localpam['L']['P'] = localpam['P']['L'] = 20;
    localpam['L']['A'] = localpam['A']['L'] = 19;
    localpam['L']['G'] = localpam['G']['L'] = 21;
    localpam['L']['N'] = localpam['N']['L'] = 20;
    localpam['L']['D'] = localpam['D']['L'] = 21;
    localpam['L']['E'] = localpam['E']['L'] = 20;
    localpam['L']['Q'] = localpam['Q']['L'] = 19;
    localpam['L']['H'] = localpam['H']['L'] = 19;
    localpam['L']['R'] = localpam['R']['L'] = 20;
    localpam['L']['K'] = localpam['K']['L'] = 20;
    localpam['L']['M'] = localpam['M']['L'] = 13;
    localpam['L']['I'] = localpam['I']['L'] = 15;

    localpam['I']['I'] = 12;
    localpam['I']['C'] = localpam['C']['I'] = 19;
    localpam['I']['S'] = localpam['S']['I'] = 18;
    localpam['I']['T'] = localpam['T']['I'] = 17;
    localpam['I']['P'] = localpam['P']['I'] = 19;
    localpam['I']['A'] = localpam['A']['I'] = 18;
    localpam['I']['G'] = localpam['G']['I'] = 20;
    localpam['I']['N'] = localpam['N']['I'] = 19;
    localpam['I']['D'] = localpam['D']['I'] = 19;
    localpam['I']['E'] = localpam['E']['I'] = 19;
    localpam['I']['Q'] = localpam['Q']['I'] = 19;
    localpam['I']['H'] = localpam['H']['I'] = 19;
    localpam['I']['R'] = localpam['R']['I'] = 19;
    localpam['I']['K'] = localpam['K']['I'] = 19;
    localpam['I']['M'] = localpam['M']['I'] = 15;

    localpam['M']['M'] = 11;
    localpam['M']['C'] = localpam['C']['M'] = 22;
    localpam['M']['S'] = localpam['S']['M'] = 19;
    localpam['M']['T'] = localpam['T']['M'] = 18;
    localpam['M']['P'] = localpam['P']['M'] = 19;
    localpam['M']['A'] = localpam['A']['M'] = 18;
    localpam['M']['G'] = localpam['G']['M'] = 20;
    localpam['M']['N'] = localpam['N']['M'] = 19;
    localpam['M']['D'] = localpam['D']['M'] = 20;
    localpam['M']['E'] = localpam['E']['M'] = 19;
    localpam['M']['Q'] = localpam['Q']['M'] = 18;
    localpam['M']['H'] = localpam['H']['M'] = 19;
    localpam['M']['R'] = localpam['R']['M'] = 17;
    localpam['M']['K'] = localpam['K']['M'] = 17;

    localpam['K']['K'] = 12;
    localpam['K']['C'] = localpam['C']['K'] = 22;
    localpam['K']['S'] = localpam['S']['K'] = 17;
    localpam['K']['T'] = localpam['T']['K'] = 17;
    localpam['K']['P'] = localpam['P']['K'] = 18;
    localpam['K']['A'] = localpam['A']['K'] = 18;
    localpam['K']['G'] = localpam['G']['K'] = 19;
    localpam['K']['N'] = localpam['N']['K'] = 16;
    localpam['K']['D'] = localpam['D']['K'] = 17;
    localpam['K']['E'] = localpam['E']['K'] = 17;
    localpam['K']['Q'] = localpam['Q']['K'] = 16;
    localpam['K']['H'] = localpam['H']['K'] = 17;
    localpam['K']['R'] = localpam['R']['K'] = 14;

    localpam['R']['R'] = 11;
    localpam['R']['C'] = localpam['C']['R'] = 21;
    localpam['R']['S'] = localpam['S']['R'] = 17;
    localpam['R']['T'] = localpam['T']['R'] = 18;
    localpam['R']['P'] = localpam['P']['R'] = 17;
    localpam['R']['A'] = localpam['A']['R'] = 19;
    localpam['R']['G'] = localpam['G']['R'] = 20;
    localpam['R']['N'] = localpam['N']['R'] = 17;
    localpam['R']['D'] = localpam['D']['R'] = 18;
    localpam['R']['E'] = localpam['E']['R'] = 18;
    localpam['R']['Q'] = localpam['Q']['R'] = 16;
    localpam['R']['H'] = localpam['H']['R'] = 15;

    localpam['H']['H'] = 11;
    localpam['H']['C'] = localpam['C']['H'] = 20;
    localpam['H']['S'] = localpam['S']['H'] = 18;
    localpam['H']['T'] = localpam['T']['H'] = 18;
    localpam['H']['P'] = localpam['P']['H'] = 17;
    localpam['H']['A'] = localpam['A']['H'] = 18;
    localpam['H']['G'] = localpam['G']['H'] = 19;
    localpam['H']['N'] = localpam['N']['H'] = 15;
    localpam['H']['D'] = localpam['D']['H'] = 16;
    localpam['H']['E'] = localpam['E']['H'] = 16;
    localpam['H']['Q'] = localpam['Q']['H'] = 14;

    localpam['Q']['Q'] = 13;
    localpam['Q']['C'] = localpam['C']['Q'] = 22;
    localpam['Q']['S'] = localpam['S']['Q'] = 18;
    localpam['Q']['T'] = localpam['T']['Q'] = 18;
    localpam['Q']['P'] = localpam['P']['Q'] = 17;
    localpam['Q']['A'] = localpam['A']['Q'] = 17;
    localpam['Q']['G'] = localpam['G']['Q'] = 18;
    localpam['Q']['N'] = localpam['N']['Q'] = 16;
    localpam['Q']['D'] = localpam['D']['Q'] = 15;
    localpam['Q']['E'] = localpam['E']['Q'] = 15;

    localpam['E']['E'] = 13;
    localpam['E']['C'] = localpam['C']['E'] = 22;
    localpam['E']['S'] = localpam['S']['E'] = 17;
    localpam['E']['T'] = localpam['T']['E'] = 17;
    localpam['E']['P'] = localpam['P']['E'] = 18;
    localpam['E']['A'] = localpam['A']['E'] = 17;
    localpam['E']['G'] = localpam['G']['E'] = 17;
    localpam['E']['N'] = localpam['N']['E'] = 16;
    localpam['E']['D'] = localpam['D']['E'] = 14;

    localpam['D']['D'] = 13;
    localpam['D']['C'] = localpam['C']['D'] = 22;
    localpam['D']['S'] = localpam['S']['D'] = 17;
    localpam['D']['T'] = localpam['T']['D'] = 17;
    localpam['D']['P'] = localpam['P']['D'] = 18;
    localpam['D']['A'] = localpam['A']['D'] = 17;
    localpam['D']['G'] = localpam['G']['D'] = 16;
    localpam['D']['N'] = localpam['N']['D'] = 15;

    localpam['N']['N'] = 15;
    localpam['N']['C'] = localpam['C']['N'] = 21;
    localpam['N']['S'] = localpam['S']['N'] = 16;
    localpam['N']['T'] = localpam['T']['N'] = 17;
    localpam['N']['P'] = localpam['P']['N'] = 18;
    localpam['N']['A'] = localpam['A']['N'] = 17;
    localpam['N']['G'] = localpam['G']['N'] = 17;

    localpam['G']['G'] = 12;
    localpam['G']['C'] = localpam['C']['G'] = 20;
    localpam['G']['S'] = localpam['S']['G'] = 16;
    localpam['G']['T'] = localpam['T']['G'] = 17;
    localpam['G']['P'] = localpam['P']['G'] = 18;
    localpam['G']['A'] = localpam['A']['G'] = 16;

    localpam['A']['A'] = 15;
    localpam['A']['C'] = localpam['C']['A'] = 19;
    localpam['A']['S'] = localpam['S']['A'] = 16;
    localpam['A']['T'] = localpam['T']['A'] = 16;
    localpam['A']['P'] = localpam['P']['A'] = 16;

    localpam['P']['P'] = 11;
    localpam['P']['C'] = localpam['C']['P'] = 20;
    localpam['P']['S'] = localpam['S']['P'] = 16;
    localpam['P']['T'] = localpam['T']['P'] = 17;

    localpam['T']['T'] = 14;
    localpam['T']['C'] = localpam['C']['T'] = 19;
    localpam['T']['S'] = localpam['S']['T'] = 16;

    localpam['S']['S'] = 15;
    localpam['S']['C'] = localpam['C']['S'] = 17;

    localpam['C']['C'] = 5;

    cout << "   ";
    for (unsigned int i = 0; i < sizeof(order); i++)
        cout << order[i] << "   ";
    cout << endl;
    for (unsigned int j = 0; j < sizeof(order); j++)
    {
        cout << order[j] << " ";
        for (unsigned int i = 0; i < sizeof(order); i++)
            cout << setfill('0') << setw(2) << localpam[(int)order[i]][(int)order[j]] << "  ";
        cout << endl;
    }
    cout << endl;
}

int main(void)
{
    initpam();
    cout << "   ";
    for (unsigned int i = 0; i < sizeof(order); i++)
        cout << order[i] << "   ";
    cout << endl;
    for (unsigned int j = 0; j < sizeof(order); j++)
    {
        cout << order[j] << " ";
        for (unsigned int i = 0; i < sizeof(order); i++)
            cout << setfill('0') << setw(2) << Cost::cost(order[i], order[j]) << "  ";
        cout << endl;
    }

    cout << "Checking PAM-250 values...\n";
    for (unsigned int j = 0; j < sizeof(order); j++)
    {
        for (unsigned int i = 0; i < sizeof(order); i++)
            if (Cost::cost(order[i], order[j]) != localpam[(int)order[i]][(int)order[j]])
                cout << "Error: " << order[i] << "/" << order[j] << " = " << localpam[(int)order[i]][(int)order[j]] << endl;
    }
    cout << "done!\n";

    return 0;
}

/*!
 * \filename read_fasta.cpp
 * \author Daniel Sundfeld
 *
 * INSERT_LICENSE
 */
#include <fstream>
#include <iostream>

#include "Sequences.h"

using namespace std;

/*!
 * Read the \a name fasta file, loading it to the Sequences singleton
 */
int read_fasta_file(const char name[])
{
    ifstream file(name);
    Sequences *sequences = Sequences::getInstance();

    if (!file.is_open())
    {
        cout << "Can't open file " << name << endl;
        return -1;
    }

    while (!file.eof())
    {
        string seq;
        while (!file.eof())
        {
            string buf;
            getline(file, buf);
            if ((buf.length() <= 0) || (buf.at(0) == '>'))
                break;
            seq.append(buf);
        }
        if (!seq.empty())
            sequences->set_seq(seq);
    }
    return 0;
}

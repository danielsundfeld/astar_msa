/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <fstream>
#include <iostream>
#include <string>

#include "Sequences.h"

/*!
 * Read the \a name fasta file, loading it to the Sequences singleton
 */
int read_fasta_file(const char name[])
{
    std::ifstream file(name);
    Sequences *sequences = Sequences::getInstance();

    if (!file.is_open())
    {
        std::cout << "Can't open file " << name << std::endl;
        return -1;
    }

    while (!file.eof())
    {
        std::string seq;
        while (!file.eof())
        {
            std::string buf;
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

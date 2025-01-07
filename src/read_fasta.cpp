/*!
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "read_fasta.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Sequences.h"

int read_fasta_file_core(const std::string &name)
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
        {
            for (auto & c: seq) c = toupper(c);
            sequences->set_seq(seq);
        }
    }
    return 0;
}

/*!
 * Read the \a name fasta file, loading it to the Sequences singleton
 */
int read_fasta_file(const std::string &name)
{
    try
    {
        return read_fasta_file_core(name);
    }
    catch (std::exception &e)
    {
        std::cerr << "Reading file fatal error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error while reading file!\n";
    }
    return -1;
}

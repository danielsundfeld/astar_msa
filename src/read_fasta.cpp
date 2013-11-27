#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Sequences.h"

using namespace std;

int read_fasta_file(const char nome[])
{
    ifstream file(nome);
    Sequences *sequences = Sequences::getInstance();

    if (!file.is_open())
    {
        cout << "Can't open file " << nome << "\n";
        return -1;
    }
    else
    {
        string buf;
        getline(file, buf);
        if ((buf.length() <= 0) || (buf.at(0) != '>'))
        {
            cout << "Invalid fasta file.\n";
            return -1;
        }
    }

    while (!file.eof())
    {
        string seq;
        while (!file.eof())
        {
            string buf;
            getline(file, buf);
            if ((buf.length() <= 0) || buf.at(0) == '>')
                break;
            seq.append(buf);
        }
        sequences->set_seq(seq);
    }
    return 0;
}


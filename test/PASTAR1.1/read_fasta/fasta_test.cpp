#include <iostream>

#include "read_fasta.h"
#include "Sequences.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [fasta_file]\n";
        return -1;
    }
    if (read_fasta_file(argv[1]))
    {
        std::cerr << "Error loading fasta arq.fasta\n";
        return -1;
    }
    std::cout << Sequences::get_seq_num();
    for (int i = 0; i < Sequences::get_seq_num(); ++i)
    {
        std::cout << " " << Sequences::getInstance()->get_seq(i).length();
    }
    std::cout << std::endl;
    return 0;
}

#include <iostream>

using namespace std;

#include "AStar.h"
#include "HeuristicAllP2.h"
#include "read_fasta.h"

int usage(char progname[])
{
    cout << "Usage:\n" << progname << " <fasta_file>\n";
    return -1;
}

int main(int argc, char *argv[])
{
    if ((argc == 1) || (read_fasta_file(argv[1]) != 0))
        return usage(argv[0]);

    HeuristicAllP2::getInstance()->init();

    return a_star();
}


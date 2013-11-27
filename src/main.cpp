#include <stdio.h>
#include <stdlib.h>

#include "AStar.h"
#include "read_fasta.h"

int usage(char progname[])
{
    printf("Usage:\n<%s> <fasta_file>.\n", progname);
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        return usage(argv[0]);
    if (read_fasta_file(argv[1]) != 0)
        return -1;
    return a_star();
}


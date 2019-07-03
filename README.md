# PA-Star

PA-Star is a software that performs a parallel A-Star search to solve the Multiple Sequence Alignment (MSA) problem. We also developed a serial version (msa\_astar).

## Getting Started

The PA-Star have been developed for Linux. The software is stable, have been stress tested on machines with 1TB of memory. The memory requirement usually is the main issue for the MSA problem. 

### Prerequisites

You need a modern C++ compiler and the libboost devel package. In Ubuntu, you can install it by:

```
sudo apt-get install build-essential libboost-dev
```

### Compiling

To compile, you enter the "astar\_msa" folder and type:

```
'make'
```

This works in all major Linux distributions and the 'msa\_astar' and 'msa\_pastar' binaries will be available in the 'astar\_msa/bin' folder.  

## How to execute

In the project we included many examples. By default, you can run msa\_astar for serial executions and msa\_pastar for parallel executions using as many cores as possible in the machine.

Few examples:
```
#Easy test:
./bin/msa_astar seqs/3/synthetic_easy.fasta

#Medium test:
./bin/msa_astar seqs/4/3pmg_ref1.fasta

#Harder test:
./bin/msa_pastar ./seqs/5/EASY_instances/synthetic_easy.fasta

#Running the parallel version in 2 processors:
./bin/msa_pastar -t 2 ./seqs/4/3pmg_ref1.fasta
```

### More options

Usually the default options are the best to run. You can change and check more at:

```
./bin/msa_astar -h or ./bin/msa_pastar -h
```

### Does it works in other problems or just the multiple sequence alignment?

Yes, the A\* algorithm is usefull for any pathfinding problem! But this project only implements MSA. If you need to use it in other problem, the function 'msa\_astar' is specific for the MSA problem, but the PriorityList class can be reused for any kind of graph.
You can also implement any 'best-first search' algorithm using the PriorityList class, by changing the rules on how you insert the nodes in the list.

## Cite us
Daniel Sundfeld, Caina Razzolini, George Teodoro, Azzedine Boukerche, Alba Cristina Magalhaes Alves de Melo: PA-Star: A disk-assisted parallel A-Star strategy with locality-sensitive hash for multiple sequence alignment.  J. Parallel Distrib. Comput. 112: 154-165 (2018)

## Documentation
This is a small scientific project, but we have professional
standards in our code and documentation. You can generate
the Doxygen documentation by running 'make' command in the
'astar\_msa/doc' folder.

## License

This project is licensed under the MIT License

# PA-Star2

PA-Star is a software that performs a parallel A-Star search to solve the Multiple Sequence Alignment (MSA) problem. For comparison we also developed a serial version (msa\_astar).

PA-Star2 is a new version with several improvements on the performance. A new Workload Distribution Vector Technique has been developed, where you can distribute the work among the threads on Asymmetric Processors (Like Intel 12th to 14th Gen.). More details, check our paper (Cite us section).

## Getting Started

The PA-Star has been developed for Linux. The software is stable and has been stress tested using machines with 1TB of memory. The memory requirement usually is the main issue for the MSA problem.

### Prerequisites

You need a modern C++ compiler and the libboost devel package. On Ubuntu, you can install it by:

```
sudo apt-get install build-essential libboost-dev
```

### Compiling

To compile, you enter the "astar\_msa" folder and type:

```
'make'
```

This command works on all major Linux distributions and the 'msa\_astar' and 'msa\_pastar' binaries will be available in the 'astar\_msa/bin' folder.

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

#Running the parallel version with 2 processors:
./bin/msa_pastar -t 2 ./seqs/4/3pmg_ref1.fasta

#Saving the output as a fasta "output.fasta" file
./bin/msa_pastar -f output.fasta seqs/3/synthetic_veryeasy.fasta

#PA-Star2 asymmetric processor distribution.
#Set the affinity for Intel i7-13700k and use a
#1:1 proportion between P-Cores and E-Cores (symetric distribution)
./bin/msa_pastar -t 16 --affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23 --hybrid=8,1,8,1 ./seqs/Balibase/Ref1/0_short_low_id/1aboA.fasta

#PA-Star2 asymmetric processor distribution.
#Set the affinity for Intel i7-13700k and use a
#9:7 proportion between P-Cores and E-Cores (assymetric distribution)
./bin/msa_pastar -t 16 --affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23 --hybrid=8,9,8,7 ./seqs/Balibase/Ref1/0_short_low_id/1aboA.fasta
```
### More options

Usually the default options are the best to run. You can change and check more at:

```
./bin/msa_astar -h or ./bin/msa_pastar -h
```

### Does it work with other problems or just the multiple sequence alignment?

Yes, the A\* algorithm is useful for any pathfinding problem! But this project only implements MSA. If you need to use it on another problem, the function 'msa\_astar' is specific for the MSA problem, but the PriorityList class can be reused for any kind of graph.
You can also implement any 'best-first search' algorithm using the PriorityList class, by changing the rules on how you insert the nodes in the list.

## Cite us
Daniel Sundfeld, George Teodoro, Alba Cristina Magalhaes Alves de Melo: PA-Star2: Fast Optimal Multiple Sequence
Alignment for Asymmetric Multicore Processors. In 33rd Euromicro International Conference on Parallel, Distributed and Network-based Processing (PDP 2025), Torino, Italy, 2025, pp. 146-153

## List of previous papers
Daniel Sundfeld, Caina Razzolini, George Teodoro, Azzedine Boukerche, Alba Cristina Magalhaes Alves de Melo: PA-Star: A disk-assisted parallel A-Star strategy with locality-sensitive hash for multiple sequence alignment.  Journal of Parallel and Distributed Computing 112: 154-165 (2018)

Daniel Sundfeld, George Teodoro, Alba Cristina Magalhaes Alves de Melo: Parallel A-Star Multiple Sequence Alignment with Locality-Sensitive Hash Functions, 2015 Ninth International Conference on Complex, Intelligent, and Software Intensive Systems (CISIS 2015), Santa Catarina, Brazil, 2015, pp. 342-347

## Documentation
This is a small scientific project, but we have professional
standards on our code and documentation. You can generate
the Doxygen documentation by running 'make' command in the
'doc/' folder.

## License

This project is licensed under the MIT License

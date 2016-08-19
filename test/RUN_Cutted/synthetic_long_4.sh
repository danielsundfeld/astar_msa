#!/bin/bash
#SBATCH -J pastar_synthethic_long_32           # job name
#SBATCH -o Pipeline.o%j       # output and error file name (%j expands to jobID)
#SBATCH -n 1              # total number of mpi tasks requested
#SBATCH -N 1             # total number of mpi tasks requested
#SBATCH -p largemem     # queue (partition) -- normal, development, etc.
#SBATCH -t 06:00:00        # run time (hh:mm:ss) - 1.5 hours
#SBATCH --mail-type=begin  # email me when the job starts
#SBATCH --mail-type=end    # email me when the job finishes
#SBATCH -A TG-ASC130023
module swap intel gcc/4.7.1

SEQ="../../seqs/Benchmark/synthethic_long.fasta"
CMD="../../bin/msa_pastar"

THREADS="-t 4"
HASH="-y FZORDER"
HASH_SHIFT="-s 12"
OPT="$THREADS $HASH $HASH_SHIFT"


strace -ve wait4 /usr/bin/time -v $CMD $OPT $SEQ >> synthethic_long_pastar_4.output 2>&1

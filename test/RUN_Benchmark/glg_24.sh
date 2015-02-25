#!/bin/bash
#SBATCH -J pastar_glg_24           # job name
#SBATCH -o Pipeline.o%j       # output and error file name (%j expands to jobID)
#SBATCH -n 1              # total number of mpi tasks requested
#SBATCH -N 1             # total number of mpi tasks requested
#SBATCH -p largemem     # queue (partition) -- normal, development, etc.
#SBATCH -t 06:00:00        # run time (hh:mm:ss) - 1.5 hours
#SBATCH --mail-type=begin  # email me when the job starts
#SBATCH --mail-type=end    # email me when the job finishes
#SBATCH -A TG-ASC130023
module swap intel gcc/4.7.1

SEQ="../../seqs/Benchmark/glg_cutted.fasta"
CMD="../../src/msa_pastar"

THREADS="-t 24"
HASH="-y FZORDER"
HASH_SHIFT="-s 12"
OPT="$THREADS $HASH $HASH_SHIFT"


/usr/bin/time -v $CMD $OPT $SEQ > glg_24.output 2>&1

#!/bin/bash
#SBATCH -J astar           # job name
#SBATCH -o Pipeline.o%j    # output and error file name (%j expands to jobID)
#SBATCH -n 1               # total number of mpi tasks requested
#SBATCH -N 1               # total number of mpi tasks requested
#SBATCH -p largemem        # queue (partition) -- normal, development, etc.
#SBATCH -t 06:00:00        # run time (hh:mm:ss) - 1.5 hours
#SBATCH --mail-type=begin  # email me when the job starts
#SBATCH --mail-type=end    # email me when the job finishes
#SBATCH -A TG-ASC130023
module swap intel gcc/4.9.1

SEQ="../../seqs/5/EASY_instances/synthetic_easy.fasta"
CMD="../../bin/msa_pastar"

for TH in 01 02 04 08 16 32; do
THREADS="-t $TH"
OPT="$THREADS"

for try in 1 2 3 4 5; do
strace -ve wait4 /usr/bin/time -v $CMD $OPT $SEQ >> $SEQ.$TH.output 2>&1
done
done

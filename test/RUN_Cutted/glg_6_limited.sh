#!/bin/bash
#SBATCH --mem 5120
#SBATCH -J astar           # job name
#SBATCH -o Pipeline.o%j       # output and error file name (%j expands to jobID)
#SBATCH -n 1              # total number of mpi tasks requested
#SBATCH -N 1             # total number of mpi tasks requested
#SBATCH -p largemem     # queue (partition) -- normal, development, etc.
#SBATCH -t 06:00:00        # run time (hh:mm:ss) - 1.5 hours
#SBATCH --mail-type=begin  # email me when the job starts
#SBATCH --mail-type=end    # email me when the job finishes
#SBATCH -A TG-ASC130023
module swap intel gcc/4.7.1
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SEQ="../../seqs/Balibase/Ref1/7_long_medium_id/glg.fasta"
CMD="../../bin/msa_pastar"

THREADS="-t 6"
OPT="$THREADS"

cd $DIR"/../../seqs/Benchmark"

strace -ve wait4 /usr/bin/time -v $CMD $OPT $SEQ > $SEQ.output 2>&1

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

./3pgm_01.sh
./3pgm_02.sh
./3pgm_04.sh
./3pgm_08.sh
./3pgm_16.sh
./3pgm_32.sh
./synth2_01.sh
./synth2_02.sh
./synth2_04.sh
./synth2_08.sh
./synth2_16.sh
./synth2_32.sh

#!/bin/bash
#SBATCH -J astar           # job name
#SBATCH -o Pipeline.o%j       # output and error file name (%j expands to jobID)
#SBATCH -n 1              # total number of mpi tasks requested
#SBATCH -N 1             # total number of mpi tasks requested
#SBATCH -p largemem     # queue (partition) -- normal, development, etc.
#SBATCH -t 03:00:00        # run time (hh:mm:ss) - 1.5 hours
#SBATCH --mail-type=begin  # email me when the job starts
#SBATCH --mail-type=end    # email me when the job finishes
#SBATCH -A TG-ASC130023

./1aab.sh
./1aboA.sh
./1ac5.sh
./1ad2.sh
./1ad3.sh
./1adj.sh
./1aho.sh
./1ajsA.sh
./1amk.sh
./1ar5A.sh
./1aym3.sh
./1bbt3.sh
./1bgl.sh
./1cpt.sh
./1csp.sh
./1csy.sh
./1dlc.sh
./1dox.sh
./1eft.sh
./1ezm.sh
./1fieA.sh
./1fjlA.sh
./1fkj.sh
./1fmb.sh
./1gdoA.sh
./1gowA.sh
./1gtr.sh
./1hfh.sh
./1hpi.sh
./1hvA.sh
./1idy.sh
./1krn.sh
./1ldg.sh
./1led.sh
./1lvl.sh
./1mrj.sh
./1ped.sh
./1pfc.sh
./1pgtA.sh
./1pii.sh
./1pkm.sh
./1plc.sh
./1ppn.sh
./1psyA.sh
./1r69.sh
./1rthA.sh
./1sbp.sh
./1tgxA.sh
./1thm.sh
./1tis.sh
./1ton.sh
./1tvxA.sh
./1ubi.sh
./1uky.sh
./1wit.sh
./1ycc.sh
./1zin.sh
./2ack.sh
./2cba.sh
./2fxb.sh
./2hsdA.sh
./2mhr.sh
./2myr.sh
./2pia.sh
./2trx.sh
./3cyr.sh
./3grs.sh
./3pgm.sh
./451c.sh
./4enl.sh
./5ptp.sh
./9rnt.sh
./actin.sh
./glg.sh
./kinase.sh

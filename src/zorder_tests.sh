#!/bin/sh

THR="2 4 8 16"
SEQS="../seqs/3/synthetic_easy.fasta ../seqs/4/3pmg_ref1.fasta ../seqs/5/EASY_instances/synthetic_easy.fasta"
SHF="1 2 3 4 5 7 9 11 13 14 15 16 17 20 23 25 27 30"

#part-z-order
echo PART_ZORDER
for thr in $THR; do
    for shif in $SHF; do
        echo THREADS: $thr SHIFT: $shif;
        make -B THREADS=$thr HASH_SHIFT=$shif HASH=PZORDER RELEASE=yes
        for file in $SEQS; do
            name=`echo $file | sed "s/.*\(seqs\/[0-9]\).*/\1/g" | sed "s/\//_/"`
            outputname=`echo part_zorder_${name}_th${thr}_shift${shif}`
            echo $outputname
            for i in `seq 10`; do
                perf stat ./msa_pastar $file
            done > $outputname 2>&1
        done
    done
done

#full-z-order
echo FULL_ZORDER
for thr in $THR; do
    for shif in $SHF; do
        echo THREADS: $thr SHIFT: $shif;
        make -B THREADS=$thr HASH_SHIFT=$shif HASH=FZORDER RELEASE=yes
        for file in $SEQS; do
            name=`echo $file | sed "s/.*\(seqs\/[0-9]\).*/\1/g" | sed "s/\//_/"`
            outputname=`echo full_zorder_${name}_th${thr}_shift${shif}`
            echo $outputname
            for i in `seq 10`; do
                perf stat ./msa_pastar $file
            done > $outputname 2>&1
        done
    done
done

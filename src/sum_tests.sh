#!/bin/sh

THR="2 4 8 16"
SEQS="../seqs/3/synthetic_easy.fasta ../seqs/4/3pmg_ref1.fasta ../seqs/5/EASY_instances/synthetic_easy.fasta"
SHF=`seq 13`

#part-sum
echo PART_SUM
for thr in $THR; do
    for shif in $SHF; do
        echo THREADS: $thr SHIFT: $shif;
        make -B THREADS=$thr HASH_SHIFT=$shif HASH=PSUM RELEASE=yes
        for file in $SEQS; do
            name=`echo $file | sed "s/.*\(seqs\/[0-9]\).*/\1/g" | sed "s/\//_/"`
            outputname=`echo part_sum_${name}_th${thr}_shift${shif}`
            echo $outputname
            for i in `seq 10`; do
                perf stat ./msa_pastar $file
            done > $outputname 2>&1
        done
    done
done

#full-sum
echo FULL_SUM
for thr in $THR; do
    for shif in $SHF; do
        echo THREADS: $thr SHIFT: $shif;
        make -B THREADS=$thr HASH_SHIFT=$shif HASH=FSUM RELEASE=yes
        for file in $SEQS; do
            name=`echo $file | sed "s/.*\(seqs\/[0-9]\).*/\1/g" | sed "s/\//_/"`
            outputname=`echo full_sum_${name}_th${thr}_shift${shif}`
            echo $outputname
            for i in `seq 10`; do
                perf stat ./msa_pastar $file
            done > $outputname 2>&1
        done
    done
done

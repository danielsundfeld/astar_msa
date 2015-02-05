#!/bin/bash

for i in $(find -name *output | sort -V); do
    name=$(basename $i: | sed "s/.fasta.output//")
    fasta_file=$(echo $i | sed "s/.output//")
    size_biggest=$(cat $fasta_file | wc -L - | sed "s/ -//")
    size_smallest=$(for j in `cat $fasta_file | grep -v "^>"`; do echo $j | wc -c; done | sort -V | head -n 1)
    num_seq=$(cat $fasta_file | grep -v "^>" | wc -l)
    p1=$(cat $i | grep "Phase 1" | awk '{print $6}')
    p2=$(cat $i | grep "Phase 2" | awk '{print $6}')
    p3=$(cat $i | grep "Phase 3" | awk '{print $5}')
    total=$(cat $i | grep "Elapsed" | awk '{print $8}')

    echo $name $num_seq $size_smallest $size_biggest $p1 $p2 $p3 $total
done

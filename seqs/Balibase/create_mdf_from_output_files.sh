#!/bin/bash
#After running a test with Balibase, parse the results to mdf files so you can compare the baliscore
FILE=$(find -name *fasta.output)

for i in $FILE; do
    fasta_file=$(echo $i | sed "s/.output//")
    s1=$(cat $fasta_file | grep "^>" | sed "s/>//g" | tr "\n" " ")
    seqs_name=($s1)
    s2=$(cat $i | sed -n -e '/Similarity/,$p' | sed -e '/Phase 3/,$d' | grep -v Similarity| sed "/^$/d" | sed 's/-/./g')
    seqs=($s2)

    i=0
    saida_file=$(echo ${fasta_file}.output.msf | sed "s/.fasta//")

    echo // > $saida_file
    echo >> $saida_file
    echo >> $saida_file

    for my_seq in ${seqs_name[@]}; do
        printf '%s        1  %s\n' ${seqs_name[$i]} ${seqs[$i]}
        let i=i+1
    done >> $saida_file
    echo >> $saida_file
    cat $saida_file
    #echo $seqs_name
    #echo $seqs
done

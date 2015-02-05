#!/bin/bash
#Script that helps to download a file from balibase to a fasta format

seqs=$(cat $1 | grep -e "  *1  " | awk '{print $1}')

for i in $seqs; do
    echo ">"$i;
    lin=$(cat $1 | grep $i | awk '{print $3}' | sed "s/\.//g")
    echo "${lin^^}" | xargs -n1 echo -n
    echo
done

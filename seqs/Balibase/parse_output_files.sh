#!/bin/bash
#script that read all outputs after run a test with Balibase sequences

#Change this to where you compile the Balibase bali_score program
BALIBASE_COMMAND="../../../Downloads/BAliBASE_R9/src/bali_score"

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
    memory=$(expr `cat $i | grep "Maximum resident set size" | awk '{print $6}'` / 1024 2>/dev/null)

    #created by create_mdf_from_output_files.sh
    msf_file=$(echo $i | sed "s/fasta.output/output.msf/")
    if [ -e $msf_file ]; then
        ref_msf_file=$(echo $msf_file | sed "s/.output//" | sed "s/Ref1/MSF_Ref1/")
        sp_score=$(${BALIBASE_COMMAND} $ref_msf_file $msf_file | grep auto | awk '{print $3}')
        tc_score=$(${BALIBASE_COMMAND} $ref_msf_file $msf_file | grep auto | awk '{print $4}')
    fi

    echo $name $num_seq $size_smallest $size_biggest $p1 $p2 $p3 $total $memory $sp_score $tc_score
done

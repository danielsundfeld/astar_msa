#!/bin/bash
SEQS="./seqs/Balibase/Ref1/0_short_low_id/1aboA.fasta ./seqs/Balibase/Ref1/3_medium_low_id/1hvA.fasta ./seqs/Balibase/Ref1/3_medium_low_id/1sbp.fasta ./seqs/Balibase/Ref1/7_long_medium_id/2ack.fasta ./seqs/Balibase/Ref1/4_medium_med_id/2cba.fasta ./seqs/Balibase/Ref1/8_long_high_id/actin.fasta ./seqs/Balibase/Ref1/7_long_medium_id/glg.fasta"

THREADS="-t 16"

git checkout "5b62293e"
if [ $? != 0 ]; then
    echo ERROR REVERTING TO NOMAP VERSION
    exit 1;
fi
make -j 16 -B

#Affinity for Intel 13700kf
AFFINITY="--affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23"
for SEQ in $SEQS; do
    echo $SEQ
    /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} $SEQ >> ${SEQ}.nomap.out 2>&1
done
git checkout master

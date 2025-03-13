#!/bin/bash
SEQ="./seqs/Balibase/Ref1/7_long_medium_id/2ack.fasta"
AFFINITY="--affinity=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31"

SHIFT="8"
ARGS="-s ${SHIFT} -t 32"
echo $SHIFT
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} $SEQ >> ${SEQ}.shif${SHIFT}.map.v3.out 2>&1
SHIFT="12"
ARGS="-s ${SHIFT} -t 32"
echo $SHIFT
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} $SEQ >> ${SEQ}.shif${SHIFT}.map.v3.out 2>&1
SHIFT="16"
ARGS="-s ${SHIFT} -t 32"
echo $SHIFT
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} $SEQ >> ${SEQ}.shif${SHIFT}.map.v3.out 2>&1

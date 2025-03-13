#!/bin/bash
SEQ="./seqs/Balibase/Ref1/7_long_medium_id/2ack.fasta"
SHIFT="16"
ARGS="-s ${SHIFT} -t 32"
AFFINITY="--affinity=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31"

pcore="1"
ecore="1"
HYBRID="16,$pcore,16,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
pcore="2"
ecore="1"
HYBRID="16,$pcore,16,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
pcore="2"
ecore="2"
HYBRID="16,$pcore,16,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
pcore="3"
ecore="1"
HYBRID="16,$pcore,16,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
pcore="3"
ecore="2"
HYBRID="16,$pcore,16,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
pcore="3"
ecore="3"
HYBRID="16,$pcore,16,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
for pcore in $(seq 4 16); do
    for ecore in $(seq $(expr $pcore - 3 ) $pcore); do
        HYBRID="16,$pcore,16,$ecore"
        echo $HYBRID
    	/usr/bin/time -v ./bin/msa_pastar ${ARGS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.shif${SHIFT}.map.${HYBRID}.out 2>&1
    done
done

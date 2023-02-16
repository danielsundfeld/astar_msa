#!/bin/bash
SEQ="./seqs/Balibase/Ref1/4_medium_med_id/2cba.fasta"
THREADS="-t 16"

#Affinity for Intel 13700kf
AFFINITY="--affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23"

pcore="1"
ecore="1"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="2"
ecore="1"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="2"
ecore="2"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="3"
ecore="1"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="3"
ecore="2"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="3"
ecore="3"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
for pcore in $(seq 4 16); do
    for ecore in $(seq $(expr $pcore - 3 ) $pcore); do
        HYBRID="8,$pcore,8,$ecore"
        echo $HYBRID
    	/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
    done
done

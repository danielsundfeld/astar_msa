#!/bin/bash
SEQ="./seqs/Balibase/Ref1/7_long_medium_id/1sesA.fasta"
THREADS="-t 16"

#Affinity for Intel 13700kf
AFFINITY="--affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23"

pcore="1"
ecore="1"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.priorityovertime.${HYBRID}.out 2>&1
pcore="9"
ecore="7"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.priorityovertime.${HYBRID}.out 2>&1

THREADS="-t 2"
AFFINITY="--affinity=0,16"
pcore="1"
ecore="1"
HYBRID="1,$pcore,1,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.priorityovertime.${HYBRID}.out 2>&1
pcore="9"
ecore="7"
HYBRID="1,$pcore,1,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.priorityovertime.${HYBRID}.out 2>&1

THREADS="-t 1"
AFFINITY="--affinity=0"
pcore="1"
ecore="1"
HYBRID="1,$pcore,0,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.priorityovertime.${HYBRID}.out 2>&1

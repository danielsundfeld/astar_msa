#!/bin/bash
SEQ="./seqs/Balibase/Ref1/6_long_low_id/2myr.fasta"
THREADS="-t 16"

#Affinity for Intel 13700kf
AFFINITY="--affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23"

pcore="5"
ecore="3"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="9"
ecore="7"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="10"
ecore="8"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="12"
ecore="10"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1
pcore="13"
ecore="13"
HYBRID="8,$pcore,8,$ecore"
echo $HYBRID
/usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.map.${HYBRID}.out 2>&1

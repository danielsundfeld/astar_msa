#!/bin/bash
SEQ="./seqs/Balibase/Ref1/7_long_medium_id/1sesA.fasta"
THREADS="-t 8"

#Affinity for Intel 13700kf
P_AFFINITY="--affinity=0,2,4,6,8,10,12,14"
E_AFFINITY="--affinity=16,17,18,19,20,21,22,23"
H_AFFINITY="--affinity=0,2,4,6,16,17,18,19"

echo Turning off super user requirement for energy consumption measuring. Please type sudo password
sudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'
sudo sysctl -w kernel.perf_event_paranoid=-1

pcore="1"
ecore="1"
HYBRID="4,$pcore,4,$ecore"
echo $HYBRID
perf stat -r 3 -e power/energy-cores/ ./bin/msa_pastar ${THREADS} ${P_AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.energy.1p.${HYBRID}.out 2>&1

pcore="9"
ecore="7"
HYBRID="4,$pcore,4,$ecore"
echo $HYBRID
perf stat -r 3 -e power/energy-cores/ ./bin/msa_pastar ${THREADS} ${H_AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.energy.2h.${HYBRID}.out 2>&1

pcore="1"
ecore="1"
HYBRID="4,$pcore,4,$ecore"
echo $HYBRID
perf stat -r 3 -e power/energy-cores/ ./bin/msa_pastar ${THREADS} ${H_AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.energy.2h.${HYBRID}.out 2>&1

pcore="1"
ecore="1"
HYBRID="4,$pcore,4,$ecore"
echo $HYBRID
perf stat -r 3 -e power/energy-cores/ ./bin/msa_pastar ${THREADS} ${E_AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.energy.3e.${HYBRID}.out 2>&1

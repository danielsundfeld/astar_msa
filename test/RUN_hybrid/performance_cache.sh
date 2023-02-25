#!/bin/bash
THREADS="-t 16"

#Affinity for Intel 13700kf
AFFINITY="--affinity=0,2,4,6,8,10,12,14,16,17,18,19,20,21,22,23"
PERF="perf stat -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,LLC-loads,LLC-load-misses,LLC-stores,LLC-prefetches"


SEQ="./seqs/Balibase/Ref1/3_medium_low_id/1sbp.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,1,8,1"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,12,8,10"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
SEQ="./seqs/Balibase/Ref1/3_medium_low_id/1hvA.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,10,8,8"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
SEQ="./seqs/Balibase/Ref1/8_long_high_id/actin.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,9,8,7"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
SEQ="./seqs/Balibase/Ref1/4_medium_med_id/2cba.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,9,8,7"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
SEQ="./seqs/Balibase/Ref1/0_short_low_id/1aboA.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,9,8,7"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
SEQ="./seqs/Balibase/Ref1/7_long_medium_id/glg.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,10,8,8"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
SEQ="./seqs/Balibase/Ref1/7_long_medium_id/2ack.fasta"
HYBRID="8,13,8,13"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1
HYBRID="8,9,8,7"
echo $SEQ/$HYBRID
${PERF} /usr/bin/time -v ./bin/msa_pastar ${THREADS} ${AFFINITY} --hybrid=${HYBRID} $SEQ >> ${SEQ}.perf.${HYBRID}.out 2>&1

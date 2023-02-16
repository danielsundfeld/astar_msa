#!/bin/bash
SEQS="./seqs/Balibase/Ref1/7_long_medium_id/glg.fasta ./seqs/Balibase/Ref1/8_long_high_id/actin.fasta ./seqs/Balibase/Ref1/3_medium_low_id/1sbp.fasta ./seqs/Balibase/Ref1/0_short_low_id/1aboA.fasta"

for try in 1 2 3 4; do
for SEQ in $SEQS; do
	for th in 1 2 4 8; do
		/usr/bin/time -v ./bin/msa_pastar_logn -t $th $SEQ >> ${SEQ}.v1.logn.th${th}.out 2>&1
		/usr/bin/time -v ./bin/msa_pastar_3tries -t $th $SEQ >> ${SEQ}.v2.3tries.th${th}.out 2>&1
		/usr/bin/time -v ./bin/msa_pastar_hash -t $th $SEQ >> ${SEQ}.v3.hash.th${th}.out 2>&1
	done
done
done

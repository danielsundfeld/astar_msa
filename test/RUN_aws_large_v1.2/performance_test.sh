#!/bin/bash
SEQS="./seqs/Balibase/Ref1/7_long_medium_id/arp.fasta ./seqs/Balibase/Ref1/7_long_medium_id/1sesA.fasta ./seqs/Balibase/Ref1/6_long_low_id/2myr.fasta ./seqs/Balibase/Ref1/8_long_high_id/1gpb.fasta"

for try in 1 2; do
for SEQ in $SEQS; do
	for th in 8 16 32 64; do
		/usr/bin/time -v ./bin/msa_pastar_logn -t $th $SEQ >> ${SEQ}.v1.logn.th${th}.out 2>&1
		aws s3 cp ${SEQ}.v1.logn.th${th}.out s3://pastarv12results/
		/usr/bin/time -v ./bin/msa_pastar_3tries -t $th $SEQ >> ${SEQ}.v2.3tries.th${th}.out 2>&1
		aws s3 cp ${SEQ}.v2.3tries.th${th}.out s3://pastarv12results/
		/usr/bin/time -v ./bin/msa_pastar_hash -t $th $SEQ >> ${SEQ}.v3.hash.th${th}.out 2>&1
		aws s3 cp ${SEQ}.v3.hash.th${th}.out s3://pastarv12results/
	done
done
done
sudo shutdown -h now

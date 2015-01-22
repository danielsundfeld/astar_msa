#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SEQ="../../seqs/Balibase/Ref1/0_short_low_id/1wit.fasta"
CMD="../../src/msa_pastar"

THREADS="-t 32"
HASH="-y FZORDER"
HASH_SHIFT="-s 12"
OPT="$THREADS $HASH $HASH_SHIFT"

cd $DIR"/../../seqs/Balibase"

/usr/bin/time -v $CMD $OPT $SEQ > $SEQ.output 2>&1

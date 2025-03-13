#!/bin/bash

for seq in $(find ../../seqs/Balibase/Ref1/ -type f -name *fasta );do

  filename=$(echo $seq | sed "s/.*\/\([0-9a-zA-Z]*\).fasta/\1/")

  echo SEQ=\"$seq\" | cat header.sh - base.sh > $filename.ru
  chmod +x $filename.ru

done

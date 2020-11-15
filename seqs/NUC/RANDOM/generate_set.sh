#Set Sequences sizes
SIZE="100 250 500 1000"
#Number of sequences
NUM_SEQ="3 4 5 6"
#Number of random fasta files
SET_SIZE=4

for i in $NUM_SEQ; do
    for j in $SIZE; do
        mkdir -p $i/$j
        for k in $(seq $SET_SIZE); do
            ./generate_random_sequence.sh $j $i > $i/$j/$k.fasta
        done
    done
done
        

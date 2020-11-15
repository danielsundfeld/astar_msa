#!/bin/sh

SIZE=100
NUM_SEQ=3

#random="$(dd if=/dev/urandom bs=1 count=1 2>/dev/null)"
function random_seq {
    for i in $(seq $SIZE); do
        num=$(expr $RANDOM % 4);
        if [ $num == 0 ]; then
            seq=$seq"C";
        elif [ $num == 1 ]; then
            seq=$seq"T";
        elif [ $num == 2 ]; then
            seq=$seq"G";
        else
            seq=$seq"A";
        fi
    done
}

if [ "$1" != "" ]; then
    if [ "$1" -gt "0" ]; then
        SIZE=$1
    fi
fi
if [ "$2" != "" ]; then
    if [ "$2" -gt "0" ]; then
        NUM_SEQ=$2
    fi
fi

for i in $(seq $NUM_SEQ); do
    echo '>'$i
    random_seq
    echo $seq
    seq=""
done

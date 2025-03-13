#!/bin/bash
LOGNVER="a1a64b13"
THREETRIESVER="0d97d597"
HASHVER="d96dccb0"
MAKEOPTS="-j 8 -B"

if [ ! -e Makefile ]; then
    echo Please run this script o astar_msa root folder
    exit 1
fi
git stash save
git checkout $LOGNVER
make $MAKEOPTS
cp ./bin/msa_pastar ./bin/msa_pastar_logn
git checkout $THREETRIESVER
make $MAKEOPTS
cp ./bin/msa_pastar ./bin/msa_pastar_3tries
git checkout $HASHVER
make $MAKEOPTS
cp ./bin/msa_pastar ./bin/msa_pastar_hash
make clean
git checkout master
git stash pop

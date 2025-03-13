#!/bin/bash
LOGNVER="64c6ed5b7ea"
THREETRIESVER="12ab8d550e"
HASHVER="5b62293e6bd"
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

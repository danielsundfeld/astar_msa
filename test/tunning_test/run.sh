#!/bin/sh
cd ../../src/
make -B THREADS=1 NO_LIB_BOOST=1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/3/synthetic_easy.fasta                >> pastar_TST1_dictionary_dynamic_03 2>&1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/4/3pmg_ref1.fasta                     >> pastar_TST1_dictionary_dynamic_04 2>&1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/5/EASY_instances/synthetic_easy.fasta >> pastar_TST1_dictionary_dynamic_05 2>&1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/22/PF07708_seed.txt                   >> pastar_TST1_dictionary_dynamic_22 2>&1

make -B THREADS=1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/3/synthetic_easy.fasta                >> pastar_TST2_multiindex_dynamic_03 2>&1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/4/3pmg_ref1.fasta                     >> pastar_TST2_multiindex_dynamic_04 2>&1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/5/EASY_instances/synthetic_easy.fasta >> pastar_TST2_multiindex_dynamic_05 2>&1
strace -ve wait4 /usr/bin/time -v ./msa_pastar ../seqs/22/PF07708_seed.txt                   >> pastar_TST2_multiindex_dynamic_22 2>&1

make clean
git checkout v1.1
cd ..
make -B
strace -ve wait4 /usr/bin/time -v ./bin/msa_pastar -t 1 ./seqs/3/synthetic_easy.fasta                >> src/pastar_TST3_multiindex_template_03 2>&1
strace -ve wait4 /usr/bin/time -v ./bin/msa_pastar -t 1 ./seqs/4/3pmg_ref1.fasta                     >> src/pastar_TST3_multiindex_template_04 2>&1
strace -ve wait4 /usr/bin/time -v ./bin/msa_pastar -t 1 ./seqs/5/EASY_instances/synthetic_easy.fasta >> src/pastar_TST3_multiindex_template_05 2>&1
strace -ve wait4 /usr/bin/time -v ./bin/msa_pastar -t 1 ./seqs/22/PF07708_seed.txt                   >> src/pastar_TST3_multiindex_template_22 2>&1

make clean
git checkout notemplate

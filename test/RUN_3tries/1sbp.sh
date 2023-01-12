#SBATCH -J dc       #Nome job
#SBATCH --time=01:00:00
#SBATCH --account=petrobrasiageo
#SBATCH --exclusive         #Utilização exclusiva dos nós
#SBATCH --mail-type=ALL
#SBATCH --mail-user=glmteodoro@gmail.com

module unload cuda/11.2  openmpi/gnu/4.1.2+cuda-11.2
module load gcc/11.1
module load openmpi/gnu/2.0.4.2
module switch boost/1.80_gnu boost/1.59_gnu

PROG_HOME="/petrobr/parceirosbr/home/george.teodoro/test/astar_msa_v1_logn"
SEQ="${PROG_HOME}/seqs/Balibase/Ref1/3_medium_low_id/1sbp.fasta"
CMD="${PROG_HOME}/bin/msa_pastar"

HASH="-y FZORDER"
HASH_SHIFT="-s 12"

for TH in 8 16 24 48; do
	THREADS="-t $TH"
	OPT="$THREADS $HASH $HASH_SHIFT"
	cd $PROG_HOME"/seqs/Balibase"
	/usr/bin/time -v $CMD $OPT $SEQ >> $SEQ.th$TH.output 2>&1
done
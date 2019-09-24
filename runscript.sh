#!/bin/bash

# Slurm configurations
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=2
#SBATCH --mem=4GB
#SBATCH --job-name=SCUBATest
#SBATCH --output=slurm_%j.out

# number of memory blocks we want to write
if [ "$1" ]
	then
		BLOCK_SIZE=$1
	else
		BLOCK_SIZE=10
fi
#dd if=/dev/zero of=./output.dat  bs=$BLOCK_SIZE  count=1;
# compile the c script
gcc testscript.c -o testfile -lm
# running the script
./testfile $BLOCK_SIZE > testresult.txt
# remove the script after running
rm testfile
# remove the data block file
#rm output.dat
# remove the output files
rm -rf tempfolder
mkdir tempfolder

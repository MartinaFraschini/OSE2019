#!/bin/bash

#SBATCH --job-name=VFI	## job name

#SBATCH --output=VFI.out		## output file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --cpus-per-task=8

#SBATCH --partition=broadwl		# partition to use

# set OMP_NUM_THREADS to the number of --cpus-per-task we asked for
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Run the process 
./VFI

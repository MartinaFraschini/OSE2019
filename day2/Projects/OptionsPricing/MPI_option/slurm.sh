#!/bin/bash

#SBATCH --job-name=BS	## job name

#SBATCH --output=BS.out		## output file

#SBATCH --ntasks=10		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
mpiexec -np $SLURM_NTASKS ./BS.exec

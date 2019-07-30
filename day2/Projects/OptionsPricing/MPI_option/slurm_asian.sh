#!/bin/bash

#SBATCH --job-name=BSasian	## job name

#SBATCH --output=BSasian.out		## output file

#SBATCH --ntasks=10		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
mpiexec -np $SLURM_NTASKS ./BSasian.exec

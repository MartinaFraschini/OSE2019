#!/bin/bash

#SBATCH --job-name=VFI	## job name

#SBATCH --output=VFI.out		## output file

#SBATCH --ntasks=10		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
mpiexec -np $SLURM_NTASKS ./VFI

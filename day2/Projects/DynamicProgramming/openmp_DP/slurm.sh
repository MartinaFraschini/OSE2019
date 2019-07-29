#!/bin/bash

#SBATCH --job-name=VFI	## job name

#SBATCH --output=VFI.out		## output file
#SBATCH --error=VFI.err		## error file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
./VFI

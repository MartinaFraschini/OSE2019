#!/bin/bash

#SBATCH --job-name=BSasian	## job name

#SBATCH --output=BSasian.out		## output file
#SBATCH --error=BSasian.err		## error file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
./BSasian.x

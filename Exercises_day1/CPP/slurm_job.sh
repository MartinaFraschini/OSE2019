#!/bin/bash

#SBATCH --job-name=helloyou	## job name

#SBATCH --output=helloyou.out		## output file
#SBATCH --error=helloyou.err		## error file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
./hidihowname.exec

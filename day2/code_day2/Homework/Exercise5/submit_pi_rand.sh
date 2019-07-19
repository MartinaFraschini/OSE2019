#!/bin/bash

#SBATCH --job-name=pi_rand	## job name

#SBATCH --output=pi_rand.out		## output file
#SBATCH --error=pi_rand.err		## error file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --partition=broadwl		# partition to use

# Run the process 
./pi_rand.x

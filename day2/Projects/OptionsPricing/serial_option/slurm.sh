#!/bin/bash

#SBATCH --job-name=BS	## job name

#SBATCH --output=BS.out		## output file
#SBATCH --error=BS.err		## error file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --account=oselab
#SBATCH --partition=sandyb		# partition to use

# Run the process 
./BS.x

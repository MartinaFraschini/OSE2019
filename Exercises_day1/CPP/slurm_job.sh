#!/bin/bash

#SBATCH --job-name=pi_findiff	## job name

#SBATCH --output=pi_findiff.out		## output file
#SBATCH --error=pi_findiff.err		## error file

#SBATCH --ntasks=1		# this job requests 1 core

#SBATCH --account=oselab
#SBATCH --partition=sandyb		# partition to use

# Run the process 
./hidihowname.exec

#!/bin/bash

#SBATCH --job-name=MCpi

#SBATCH --output=MCpi.out

# this job requests 4 MPI processes
#SBATCH --ntasks=4

# and request 8 cpus per task for OpenMP threads
#SBATCH --cpus-per-task=8

# this job will run in the broadwl partition on Midway
#SBATCH --partition=broadwl

# load the openmpi default module
module load openmpi

# set OMP_NUM_THREADS to the number of --cpus-per-task we asked for
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Run the process with mpirun. Notice -n is not required. mpirun will
# automatically figure out how many processes to run from the slurm options
mpirun ./MCpi.exec

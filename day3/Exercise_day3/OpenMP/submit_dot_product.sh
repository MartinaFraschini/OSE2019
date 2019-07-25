#!/bin/bash

# set the job name
#SBATCH --job-name=dot_prod

# send output to dot_prod.out
#SBATCH --output=dot_prod.out

# this job requests node
#SBATCH --ntasks=1

# and request cpus per task for OpenMP threads
#SBATCH --cpus-per-task=1

# set OMP_NUM_THREADS to the number of --cpus-per-task we asked for
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Run the process with mpirun. Notice -n is not required. mpirun will
# automatically figure out how many processes to run from the slurm options
### openmp executable
./dot_prod.exec

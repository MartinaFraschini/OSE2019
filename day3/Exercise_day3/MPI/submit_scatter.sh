#!/bin/bash -l

#SBATCH --job-name=scatter


#SBATCH --ntasks=10


#SBATCH --time=00:02:00

#SBATCH --output=scatter.out


### MPI executable
mpiexec -np $SLURM_NTASKS ./scatter.exec

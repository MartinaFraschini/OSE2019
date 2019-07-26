#!/bin/bash -l

#SBATCH --job-name=MCpi


#SBATCH --ntasks=10


#SBATCH --time=00:02:00

#SBATCH --output=MCpi.out


### MPI executable
mpiexec -np $SLURM_NTASKS ./MCpi.exec

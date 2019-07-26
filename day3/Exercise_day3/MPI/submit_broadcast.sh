#!/bin/bash -l

#SBATCH --job-name=broadcast


#SBATCH --ntasks=16

#SBATCH --time=00:02:00

#SBATCH --output=broadcast.out


### MPI executable
mpiexec -np $SLURM_NTASKS ./broadcast.exec

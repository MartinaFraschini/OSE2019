#!/bin/bash -l

#SBATCH --job-name=allreduce


#SBATCH --ntasks=10


#SBATCH --time=00:02:00

#SBATCH --output=allreduce.out


### MPI executable
mpiexec -np $SLURM_NTASKS ./allreduce.exec

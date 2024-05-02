#!/bin/bash -l

#SBATCH --nodes=16
#SBATCH --ntasks=16
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --output=job.out
#SBATCH --error=job.err
#SBATCH --time=01:00:00

# Load some modules & list loaded modules
module load gcc openmpi
module list

# Compile
make clean
make

# run the program on local machine
# mpirun --oversubscribe -np 16 ./ghost

# on euler
mpirun -np 16 ./ghost
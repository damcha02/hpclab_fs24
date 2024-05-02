#!/bin/bash
#SBATCH --job-name=powermethod_mpi      # Job name
#SBATCH --output=powermethod_mpi-%j.out # Output file
#SBATCH --error=powermethod_mpi-%j.err  # Error file
#SBATCH --ntasks=64                      # Adjust this later dynamically
#SBATCH --nodes=64                       # Adjust this later dynamically
#SBATCH --time=01:20:00                 # Wall clock time limit
#SBATCH --constraint=EPYC_7763          # Specific node requirement if needed


module load openmpi
module load python/3.7.4
module list  

make clean
make all

matrix_size=10000
max_iter=3000
tolerance=-1e-6

echo "---------------- Strong Scaling Test ----------------"
# Strong scaling: fixed matrix size, increasing number of processors
for n_procs in 1 2 4 8 16 32 64; do
    echo "Running with $n_procs processors on a $matrix_size x $matrix_size matrix"
    mpirun -np $n_procs ./powermethod_rows 3 $matrix_size $max_iter $tolerance
done

echo "---------------- Weak Scaling Test ----------------"
# Weak scaling: increasing matrix size with the number of processors
for n_procs in 1 2 4 8 16 32 64; do
    adjusted_size=$((10000 * (n_procs**0.5)))
    echo "Running with $n_procs processors on a $adjusted_size x $adjusted_size matrix"
    mpirun -np $n_procs ./powermethod_rows 3 $adjusted_size $max_iter $tolerance
done

echo "---------------- Plotting Results ----------------"

python plot_scaling.py

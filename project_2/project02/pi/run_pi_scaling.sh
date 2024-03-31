#!/bin/bash
#SBATCH --job-name=pi_omp      # Job name    (default: sbatch)
#SBATCH --output=pi_omp-%j.out # Output file (default: slurm-%j.out)
#SBATCH --error=pi_omp-%j.err  # Error file  (default: slurm-%j.out)
#SBATCH --ntasks=1                # Number of tasks
#SBATCH --constraint=EPYC_7763    # Select node with CPU
#SBATCH --cpus-per-task=128       # Number of CPUs per task
#SBATCH --mem-per-cpu=1024        # Memory per CPU
#SBATCH --time=00:05:00           # Wall clock time limit

# Load some modules & list loaded modules
module load gcc
module load python/3.11.6

module list

# Compile
make clean
make

echo "-----------------------------------------------"
#Run the program for reference 
# dont need threads here
echo "Running Pi SERIAL for reference and to compare"
./pi_serial
echo "-----------------------------------------------"


# Run the program for OMP_NUM_THREADS equal to 1, 2, 4, 8, ..., 64, 128
for ((i=0; i<=7; i++))
do
  OMP_NUM_THREADS=$((2**i))
  echo "Running Pi CRITICAL with OMP_NUM_THREADS=$OMP_NUM_THREADS"
  export OMP_NUM_THREADS
  ./pi_omp_critical
  echo "-----------------------------------------------"
done

# Run the program for OMP_NUM_THREADS equal to 1, 2, 4, 8, ..., 64, 128
for ((i=0; i<=7; i++))
do
  OMP_NUM_THREADS=$((2**i))
  echo "Running Pi REDUCTION with OMP_NUM_THREADS=$OMP_NUM_THREADS"
  export OMP_NUM_THREADS
  ./pi_omp_reduction
  echo "-----------------------------------------------"
done


python3 plot_scaling.py
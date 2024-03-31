#!/bin/bash
#SBATCH --job-name=mandel_benchmark      # Job name
#SBATCH --output=mandel_benchmark-%j.out # Output file
#SBATCH --error=mandel_benchmark-%j.err  # Error file
#SBATCH --ntasks=1                       # Number of tasks
#SBATCH --constraint=EPYC_7763           # Select node with CPU
#SBATCH --cpus-per-task=128              # Maximum number of CPUs per task
#SBATCH --mem-per-cpu=1024               # Memory per CPU
#SBATCH --time=00:30:00                  # Wall clock time limit

# Load modules
module load gcc/11.4.0
module load libpng/1.6.39
module list

# Compile the parallel version of the Mandelbrot program
make clean
make 

# Array of thread counts for strong scaling analysis
THREAD_COUNTS=(1 2 4 8 16 32 64 128)

# Directory to store output images and performance data
OUTPUT_DIR="./output"
mkdir -p $OUTPUT_DIR

# Run the parallel program with various numbers of threads
for THREADS in ${THREAD_COUNTS[@]}; do
    echo "Running with $THREADS threads..."
    export OMP_NUM_THREADS=$THREADS
    ./mandel_seq > $OUTPUT_DIR/mandel_omp_${THREADS}.txt
    mv mandel.png $OUTPUT_DIR/mandel_${THREADS}.png
    echo "Finished $THREADS threads."
done

echo "Benchmarking completed."
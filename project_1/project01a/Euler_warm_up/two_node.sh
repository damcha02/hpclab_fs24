#!/bin/bash
#SBATCH --job-name=hello-world-multi-node
#SBATCH --output=slurm-%j.out 
#SBATCH --error=slurm-%j.err 
#SBATCH --time=00:30:00
#SBATCH --ntasks=2
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --mem-per-cpu=1000 #adjust memory as per requirement
#SBATCH --constraint=EPYC_7742

module load gcc/9.3.0

#create a build directory if not present
# Define the directory name
dir="build"

# Check if the directory already exists
if [ -d "$dir" ]; then
    echo "Directory $dir already exists."
else
    # If the directory does not exist, create it
    mkdir -p "$dir"
    echo "Directory $dir created."
fi

#compile 
g++ -o ./build/hello_world_2 hello_world.cpp -std=c++11

#run program on two diff nodes
srun --ntasks=2 --nodes=2 --ntasks-per-node=1 hostname
srun --ntasks=2 --nodes=2 --ntasks-per-node=1 ./build/hello_world

#to run use sbatch two_node.sh

#check output with cat slurm-*.out
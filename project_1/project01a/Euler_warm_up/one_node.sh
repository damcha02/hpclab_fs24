#!/bin/bash
#SBATCH --job-name=hello-world
#SBATCH --output=hello-world-%j.out 
#SBATCH --error=hello-world-%j.err 
#SBATCH --time=00:30:00
#SBATCH --ntasks=1
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
g++ -o ./build/hello_world hello_world.cpp -std=c++11

#run it
./build/hello_world
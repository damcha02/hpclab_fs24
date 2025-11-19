# HPC Lab Project 1: Introduction to HPC Systems

A small experimental HPC project developed during my studies in Computational Science & Engineering at ETH Zurich, focusing on getting familiar with the Euler cluster environment and understanding memory hierarchies.

## Overview

This project consists of two basic exercises:
- **Euler Warm-up**: Simple "Hello World" program to test cluster access and job submission
- **Memory Hierarchies**: Studying CPU architecture specifications (AMD EPYC 7763)

## Features

- Basic C++ program for cluster environment testing
- Hostname detection and output
- Documentation study of modern HPC processor architecture

## Technologies

- C++17
- Linux
- ETH Euler cluster (SLURM)

## Build

```bash
cd Euler_warm_up
g++ hello_world.cpp -o hello_world
```

## Run

```bash
./hello_world
```

Or submit to cluster:
```bash
sbatch job_script.sh
```

## Project Status

This is an introductory warmup project.
The main goal was to familiarize myself with cluster access, job submission, and HPC hardware specifications.

## What I Learned

- Submitting jobs to HPC clusters using SLURM
- Understanding cluster node architecture
- Reading CPU specifications (cache hierarchy, memory bandwidth, core counts)
- Basic C++ compilation on Linux systems

## License

MIT License

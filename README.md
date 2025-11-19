# HPC Lab Projects (Spring 2024)

A collection of experimental HPC projects completed during my studies in Computational Science & Engineering at ETH Zurich. These projects explore parallel programming techniques, performance analysis, and distributed computing concepts.

## Overview

This repository contains four lab projects focusing on different aspects of high-performance computing:

### [Project 1: Introduction to HPC Systems](project_1/)
Introduction to the ETH Euler cluster environment and CPU architecture study.

**Key Topics:**
- Cluster access and job submission
- Memory hierarchy analysis
- SLURM basics

### [Project 2: Shared Memory Parallelization with OpenMP](project_2/)
Exploration of shared-memory parallel programming patterns using OpenMP.

**Key Topics:**
- Parallel loops and work sharing
- Synchronization mechanisms (reduction, critical sections, atomic)
- Race condition debugging
- Loop scheduling strategies
- Applications: Pi calculation, Mandelbrot set, histogram computation

### [Project 3: Mini-Stencil Application (2D Diffusion Solver)](project_3/)
Serial implementation of a 2D implicit diffusion solver using finite differences.

**Key Topics:**
- Stencil computations
- Iterative solvers (Newton method, Conjugate Gradient)
- PDE discretization
- Scientific visualization output

### [Project 4: Distributed Memory Parallelization with MPI](project_4/)
Introduction to distributed-memory programming using MPI.

**Key Topics:**
- Point-to-point and collective communication
- Domain decomposition
- Ghost cell exchange
- Load balancing
- Applications: Power method, Mandelbrot set, ring communication

## Technologies

- **Languages**: C, C++
- **Parallel APIs**: OpenMP, MPI
- **Environment**: Linux, ETH Euler cluster (SLURM)
- **Build Tools**: Make, CMake
- **Compilers**: GCC, MPI compilers (mpicc)

## Project Status

These are experimental learning projects created during coursework.
They focus on understanding parallel programming concepts and exploring performance behavior.
Some projects are incomplete or not fully optimized, as they were time-constrained academic exercises.

## What I Learned

- Fundamentals of parallel programming (shared and distributed memory models)
- Performance measurement and scaling analysis (strong/weak scaling)
- Debugging parallel code (race conditions, deadlocks, segmentation faults)
- Working with HPC cluster environments and job schedulers
- Implementing numerical algorithms (iterative solvers, stencil operations)
- Understanding communication overhead and synchronization costs
- Domain decomposition and load balancing strategies

## Structure

```
hpclab-fs24/
├── project_1/          # Cluster introduction & architecture study
├── project_2/          # OpenMP parallelization exercises
├── project_3/          # Serial 2D diffusion solver
└── project_4/          # MPI distributed programming
```

## Acknowledgments

Course: High Performance Computing Lab, ETH Zurich, Spring 2024

## License

MIT License

# HPC Lab Project 4: Distributed Memory Parallelization with MPI

An experimental HPC project developed during my studies in Computational Science & Engineering at ETH Zurich, focusing on distributed-memory parallelization using MPI (Message Passing Interface).

## Overview

This project explores MPI programming patterns through multiple exercises:
- Hello World with MPI initialization and process information
- Ring communication pattern (passing messages in a circle)
- Ghost cell exchange (halo exchange for domain decomposition)
- Power method for eigenvalue computation with row-wise matrix distribution
- Mandelbrot set generation with MPI parallelization

## Features

- Basic MPI communication patterns (point-to-point, collective)
- Domain decomposition strategies
- Load balancing across processes
- Distributed matrix-vector multiplication
- Ghost cell synchronization for PDE solvers
- Performance timing and scaling analysis

## Technologies

- C
- MPI (Message Passing Interface)
- Linux
- Makefiles
- SLURM (for cluster execution)

## Build

Each subdirectory contains its own Makefile or build instructions:

```bash
cd powermethod
make
```

Or manually:
```bash
mpicc powermethod_rows.c walltime.c -o powermethod_rows -lm
```

## Run

Example for power method:
```bash
mpirun -np 4 ./powermethod_rows 1 1024 100 1e-6
```

Example for ring communication:
```bash
mpirun -np 8 ./ring_sum
```

Example for Mandelbrot:
```bash
mpirun -np 4 ./mandel_mpi
```

## Results (Example: Power Method)

| Processes | Matrix Size | Runtime (s) |
|-----------|-------------|-------------|
| 1         | 1024        | ~0.8        |
| 4         | 1024        | ~0.25       |
| 8         | 1024        | ~0.15       |

Speedup depends on problem size, communication overhead, and load balancing.

## Project Status

This is an experimental learning project.
Core exercises (hello_mpi, ring, ghost, powermethod, mandel) are implemented.
The implementations focus on understanding MPI concepts and communication patterns rather than optimal performance.
Some parts may have inefficiencies or could be better optimized.

## What I Learned

- Fundamentals of distributed-memory programming with MPI
- Point-to-point communication (MPI_Send, MPI_Recv)
- Collective operations (MPI_Bcast, MPI_Allgather, MPI_Allgatherv, MPI_Reduce)
- Domain decomposition and data distribution strategies
- Ghost cell exchange patterns for stencil computations
- Debugging parallel programs across multiple processes
- Understanding communication overhead and strong/weak scaling
- Load balancing in distributed algorithms

## License

MIT License

# HPC Lab Project 2: Shared Memory Parallelization with OpenMP

An experimental HPC project developed during my studies in Computational Science & Engineering at ETH Zurich, focusing on shared-memory parallelization techniques using OpenMP.

## Overview

This project explores various parallel programming patterns with OpenMP through multiple exercises:
- Pi calculation using numerical integration (critical sections vs. reduction)
- Mandelbrot set generation with PNG output
- Histogram computation with parallel optimization
- Loop dependency analysis and parallelization
- Debugging OpenMP race conditions

## Features

- Multiple OpenMP parallelization strategies (reduction, critical sections, scheduling)
- Performance comparison between serial and parallel implementations
- Real-world applications (Mandelbrot visualization, numerical integration)
- Race condition debugging exercises
- Timing utilities for performance measurement

## Technologies

- C/C++
- OpenMP
- Linux
- CMake / Makefiles

## Build

Each subdirectory contains its own Makefile:

```bash
cd pi
make
```

Or for individual programs:
```bash
gcc -fopenmp pi_omp_reduction.c walltime.c -o pi_omp_reduction -lm
```

## Run

Example for Pi calculation:
```bash
./pi_omp_reduction 10000000
```

Example for Mandelbrot:
```bash
./mandel_seq
```

## Results (Example: Pi Calculation)

| Threads | Runtime (ms) | Speedup |
|---------|--------------|---------|
| 1       | ~120         | 1.0x    |
| 4       | ~35          | 3.4x    |
| 8       | ~20          | 6.0x    |

Results vary based on problem size and system architecture.

## Project Status

This is an experimental learning project.
Some exercises are complete (pi, mandelbrot, histogram), while others (quicksort parallelization) were not fully implemented.
The implementations focus on exploring OpenMP concepts rather than production optimization.

## What I Learned

- Fundamentals of OpenMP parallel programming
- Different synchronization mechanisms (critical sections, reductions, atomic operations)
- Identifying and resolving race conditions
- Loop scheduling strategies (static, dynamic, guided)
- Performance measurement and speedup analysis
- Understanding parallel overhead and scaling limitations

## License

MIT License

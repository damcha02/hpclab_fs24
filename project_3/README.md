# HPC Lab Project 3: Mini-Stencil Application (2D Diffusion Solver)

An experimental HPC project developed during my studies in Computational Science & Engineering at ETH Zurich, implementing a 2D implicit diffusion solver using finite differences and iterative methods.

## Overview

This project implements a serial solver for the 2D Fisher equation using:
- Second-order finite difference spatial discretization
- Implicit time stepping
- Newton method for nonlinear iterations
- Conjugate Gradient (CG) method for linear system solving
- Visualization output in BOV format

## Features

- 2D stencil-based PDE solver
- Newton-CG iterative solver combination
- Convergence monitoring and statistics
- Binary output for visualization
- Performance timing utilities
- Configurable mesh size, timesteps, and tolerance

## Technologies

- C++
- Linux
- Makefiles
- VisIt/ParaView compatible output format (BOV)

## Build

```bash
cd mini_app
make
```

## Run

```bash
./main nx nt t [verbose]
```

Parameters:
- `nx`: Number of gridpoints in x and y directions
- `nt`: Number of timesteps
- `t`: Total simulation time
- `verbose`: (optional) Enable detailed output

Example:
```bash
./main 128 100 0.1
```

## Results

Example output for 128x128 grid, 100 timesteps:
```
simulation took ~2.5 seconds
~15000 conjugate gradient iterations
~100 newton iterations
```

Performance scales approximately O(nx²) for mesh size.

## Project Status

This is a serial prototype implementation.
The code is functionally complete for the serial case but was intended as a baseline for future MPI/OpenMP parallelization work that was not completed.
No parallelization has been implemented.

## What I Learned

- Implementing iterative PDE solvers (Newton method, CG method)
- Finite difference discretization techniques
- Stencil operations and boundary conditions
- Structuring scientific computing applications
- Understanding convergence criteria and numerical stability
- Performance profiling of iterative solvers

## License

MIT License

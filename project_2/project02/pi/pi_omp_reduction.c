#include <stdio.h> /* printf */
#include <stdlib.h> /* atol */
#include "walltime.h"
//here we need openmp
#include <omp.h>


int main(int argc, char *argv[]) {
  long int N = 1000000;
  double time_start, h, sum, pi;

  if ( argc > 1 ) N = atol(argv[1]);

  /* Parallelize with OpenMP using the reduction clause */
  time_start = walltime();
  h = 1./N;
  sum = 0.;

  //let us parallelize the loop across the available threads
  //each thread will have a private copy of sum during the loop
  //at the end open mp will automatically add all the partial sums together
  #pragma omp parallel for reduction (+:sum) 
  for (int i = 0; i < N; ++i) {
    double x = (i + 0.5)*h;
    sum += 4.0 / (1.0 + x*x);
  }
  pi = sum*h;
  double time = walltime() - time_start;

  printf("pi = \%.15f, N = %9ld, time = %.8f secs\n", pi, N, time);

  #pragma omp parallel
  #pragma omp master //can use single instead of master
  {
    printf("nUmBeR oF tHrEAdS: %d\n", omp_get_num_threads());
  }

  return 0;
}

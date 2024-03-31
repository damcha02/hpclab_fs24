#include <stdio.h> /* printf */
#include <stdlib.h> /* atol */
#include "walltime.h"
//here we need open mp
#include <omp.h>

int main(int argc, char *argv[]) {

  
  long int N = 1000000;
  double time_start, h, sum = 0.0, pi;

  if ( argc > 1 ) N = atol(argv[1]);

  /* Parallelize with OpenMP using the critical directive */
  time_start = walltime();
  h = 1./N;

  #pragma omp parallel 
  {
    double local_sum = 0.0; //local sum for each thread
    double x;

    #pragma omp for  
    for (int i = 0; i < N; ++i) {
      x = (i + 0.5)*h;
      local_sum += 4.0 / (1.0 + x*x);
      
    }
    // printf("Thread %d\n", omp_get_thread_num());
    
    #pragma omp critical
    {
      sum += local_sum;
    }
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

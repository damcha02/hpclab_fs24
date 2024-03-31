/* FILE: omp_bug2.c
 * DESCRIPTION:
 *   Another OpenMP program with a bug.
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int nthreads, i, tid;
  float total;

/* Spawn parallel region */
  #pragma omp parallel
  {
    /* Obtain thread number */
    tid = omp_get_thread_num();
    /* Only master thread does this */
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
    printf("Thread %d is starting...\n", tid);

#pragma omp barrier //unnecessary 
//cool thing though

    /* do some work */
    total = 0.0; //this is a shared variable but...
    
    //the threads are dynamically assignent always in chunks of size 10
    //and the for loop is split up into different threads
    //the variable stays shared across all threads 
    //leading to a race condition 
    //can be solved using reduction or critical directive 
    #pragma omp for schedule(dynamic, 10)
    for (i = 0; i < 1000000; i++)
      total = total + i * 1.0;

  } /* End of parallel region */

  printf("Thread %d is done! Total= %e\n", tid, total);

}

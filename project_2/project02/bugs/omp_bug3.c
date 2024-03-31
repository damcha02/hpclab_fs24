/******************************************************************************
 * FILE: omp_bug3.c
 * DESCRIPTION:
 *   Run time error
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50

int main(int argc, char *argv[]) {
  int i, nthreads, tid, section;
  float a[N], b[N], c[N];
  void print_results(float array[N], int tid, int section);

  /* Some initializations */
  for (i = 0; i < N; i++)
    a[i] = b[i] = i * 1.0;

#pragma omp parallel private(c, i, tid, section)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }

/*** Use barriers for clean output ***/
//well this can't be right
//why, plus wrong implementation? 
//
#pragma omp barrier
    printf("Thread %d starting...\n", tid);
#pragma omp barrier

#pragma omp sections nowait
    {
#pragma omp section
      {
        section = 1;
        for (i = 0; i < N; i++)
          c[i] = a[i] * b[i];
        print_results(c, tid, section);
      }

#pragma omp section
      {
        section = 2;
        for (i = 0; i < N; i++)
          c[i] = a[i] + b[i];
        print_results(c, tid, section);
      }

    } /* end of sections */

/*** Use barrier for clean output ***/
#pragma omp barrier //
    printf("Thread %d exiting...\n", tid);

  } /* end of parallel section */
}

void print_results(float array[N], int tid, int section) {
  int i, j;

  j = 1;
/*** use critical for clean output ***/
#pragma omp critical
  {
    printf("\nThread %d did section %d. The results are:\n", tid, section);
    for (i = 0; i < N; i++) {
      printf("%e  ", array[i]);
      j++;
      if (j == 6) {
        printf("\n");
        j = 1;
      }
    }
    printf("\n");
  } /*** end of critical ***/
//this is incorrect and causes a run time error since not all threads reach it
//only the ones that enter the section reach this
//which violates the rule that all threads must reach the barrier
#pragma omp barrier
  printf("Thread %d done and synchronized.\n", tid);
}


/*
one of the fundamental rules for using barries
is that all threads in a team must reach the barrier
if any thread does not reach the barrier the program can hang 
indefinitely because the threads that have reached the barrier 
will wait forever for the others

barriers ensure that all threads have completed their work up to that point before any thread continues

-------------------------------------------------------------------------------------------------------

for loops and section blocks are implicit barriers
the nowait clause makes a section 

#pragma omp barrier is an explicit barrier

Rule of All Threads Must Reach: 
For a barrier (whether implicit or explicit) 
to work correctly, all threads in the parallel 
region must reach the barrier. If any thread skips 
the barrier (due to conditional execution paths, 
for example), it can lead to deadlocks or undefined 
behavior.

Incorrect Use Inside Conditional Blocks: 
Placing a barrier inside a conditional block
that is not guaranteed to be executed by all threads
(e.g., only executed by threads that enter a certain
section) violates the rule that all threads must
reach the barrier. This can cause a hang or crash.
*/
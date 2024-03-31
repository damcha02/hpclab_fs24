/******************************************************************************
 * FILE: omp_bug5.c
 * DESCRIPTION:
 *   Using SECTIONS, two threads initialize their own array and then add
 *   it to the other's array, however a deadlock occurs.
 ******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000
#define PI 3.1415926535
#define DELTA .01415926535

int main(int argc, char *argv[]) {
  int nthreads, tid, i;
  float a[N], b[N];
  omp_lock_t locka, lockb;

  /* Initialize the locks */
  omp_init_lock(&locka);
  omp_init_lock(&lockb);

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel shared(a, b, nthreads, locka, lockb) private(tid)
  {

    /* Obtain thread number and number of threads */
    tid = omp_get_thread_num();
#pragma omp master
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
    printf("Thread %d starting...\n", tid);
#pragma omp barrier

#pragma omp sections nowait
    {
#pragma omp section
      {
        printf("Thread %d initializing a[]\n", tid);
        omp_set_lock(&locka); //first lock acquired by first thread
        for (i = 0; i < N; i++)
          a[i] = i * DELTA;
        omp_set_lock(&lockb); //attempts to acquire the second lock while still holding  the first
        printf("Thread %d adding a[] to b[]\n", tid); 
        for (i = 0; i < N; i++)
          b[i] += a[i];
        omp_unset_lock(&lockb);
        omp_unset_lock(&locka);
      }

#pragma omp section
      {
        printf("Thread %d initializing b[]\n", tid);
        omp_set_lock(&lockb); //first lock acquired by second thread 
        //locka
        for (i = 0; i < N; i++)
          b[i] = i * PI;
        omp_set_lock(&locka);
        //lockb
        printf("Thread %d adding b[] to a[]\n", tid); //attempts to acquire the second lock while still holding the first 
        for (i = 0; i < N; i++)
          a[i] += b[i];
        omp_unset_lock(&locka);
        //lockb
        omp_unset_lock(&lockb);
        //locka
      }
    } /* end of sections */
  }   /* end of parallel region */
}
//deadlock happens because: 
//thread 1: enters first section and acquires locka, but before it can acquire lockb
//it is preemted by thread 2
//thread 2: enters second section and acquires lockb. now it attempts to acquire locka which is already held by thread 1
//so it waits
//thread 1: resumes execution and attempts to acquire lockb which is held by thread 2 and is now waiting for thread 2 to release lockb
//while thread 2 is waiting for thread 1 to release locka


//my guess is that it is wrong to set a simple lock and then another
//it should be a nested lock
//thread 1 holds locka and waits for lockb
//thread 2 holds lockb and waits for locka
//acquiring and releasing locks should be in the same order 

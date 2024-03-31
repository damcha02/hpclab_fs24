#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "walltime.h"
#include <omp.h>

int main(int argc, char *argv[]) {
  int N = 2000000000;
  double up = 1.00000001;
  double Sn = 1.00000001;
  int n;

  /* allocate memory for the recursion */
  double *opt = (double *)malloc((N + 1) * sizeof(double));
  if (opt == NULL) {
    perror("failed to allocate problem size");
    exit(EXIT_FAILURE);
  }

  double time_start = walltime();

  //value of Sn in each iteration depends on the value from 
  //its previous iteration
  //since its just alwasy * up
  //we can do Sn_initial * up^n
  //firstprivate specifies that each thread has its own instance 
  //of the variable and that the variable should be initialized
  //with the value of the variable, because it exists before the parallel construct

  //lastprivate doesnt affect the outcome of the code 
  //for the sake of learning by doing i still implented it but it doesnt work and no time/motivation to fix
/*
  #pragma omp parallel for firstprivate(Sn, up) lastprivate(n)
  for (n = 0; n <= N; ++n) {
    opt[n] = Sn * pow(up, n);
  }
*/



  #pragma omp parallel for firstprivate(Sn, up) 
  for (n = 0; n <= N; ++n) {
    opt[n] = Sn * pow(up, n);
  }

  //update Sn to its final value
  Sn *= pow(up, N+1);

  printf("Parallel RunTime  :  %f seconds\n", walltime() - time_start);
  printf("Final Result Sn   :  %.17g \n", Sn);

  double temp = 0.0;
  for (n = 0; n <= N; ++n) {
    temp += opt[n] * opt[n];
  }
  printf("Result ||opt||^2_2 :  %f\n", temp / (double)N);
  printf("\n");

  #pragma omp parallel
  #pragma omp master //can use single instead of master
  {
    printf("nUmBeR oF tHrEAdS: %d\n", omp_get_num_threads());
  }
  return 0;
}

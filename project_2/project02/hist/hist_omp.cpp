#include "walltime.h"
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>


#define VEC_SIZE 1000000000
#define BINS 16

int main() {
  double time_start, time_end;

  // Initialize random number generator
  unsigned int seed = 123;
  float mean = BINS / 2.0;
  float sigma = BINS / 12.0;
  std::default_random_engine generator(seed);
  std::normal_distribution<float> distribution(mean, sigma);

  // Generate random sequence
  // Note: normal distribution is on interval [-inf; inf]
  //       we want [0; BINS-1]
  std::vector<int> vec(VEC_SIZE);
  for (long i = 0; i < VEC_SIZE; ++i) {
    vec[i] = int(distribution(generator));
    if (vec[i] < 0       ) vec[i] = 0;
    if (vec[i] > BINS - 1) vec[i] = BINS - 1;
  }

  // Initialize histogram: Set all bins to zero
  long dist[BINS];
  for (int i = 0; i < BINS; ++i) {
    dist[i] = 0;
  }

  // TODO Parallelize the histogram computation

  time_start = walltime();

  #pragma omp parallel
  {
    //initialize a local/private histogram for each thread
    //set all bins to 0
    long local_dist[BINS];
    for(int i = 0; i < BINS; ++i){
      local_dist[i] = 0;
    }
    #pragma omp for nowait //distribute iterations among threads
    for (long i = 0; i < VEC_SIZE; ++i) {
      local_dist[vec[i]]++;
    }

    #pragma omp critical //add/merge all the local/private histograms to the global histogram
    for(int i = 0; i < BINS; ++i){
      dist[i] += local_dist[i];
    }
    
  }
  time_end = walltime();

  // Write results
  for (int i = 0; i < BINS; ++i) {
    std::cout << "dist[" << i << "]=" << dist[i] << std::endl;
  }
  std::cout << "Time: " << time_end - time_start << " sec" << std::endl;

  //just imagine how much other stuff i have wrong because i have never included this to check and just accepted it, crazy
  #pragma omp parallel
  #pragma omp master //can use single instead of master
  {
    std::cout << "Number of threads: " <<omp_get_num_threads() << std::endl;
  }
  return 0;
}

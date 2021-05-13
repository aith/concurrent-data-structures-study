#include <thread>
#include "util.h"

void parallel_pow(float * result, int *power, int size, int tid, int num_threads) {
  // write me in a SPMD parallel way!  partition the data using
  // "chunks" rather than strides.  That is thread 0 computes elements
  // 0 through size/num_threads.  thread 1 computes elements
  // size/num_threads through 2*(size/num_threads)
  for (int i = 0; i < size; i++) {
    for (int w = 0; w < power[i]-1; w++) {
      result[i] = result[i]*result[i];
    }
  }
}

int main() {
  float* result_parallel = new float[SIZE];
  int* power = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    result_parallel[i] = i;
  }
  linear_work(power, SIZE);

  // Launch NUM_THREADS threads and then join them
}

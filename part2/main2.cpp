#include <thread>
#include <atomic>
#include "util.h"

std::atomic_int counter(0);
void parallel_pow(float * result, int *power, int size, int tid, int num_threads) {
  // Write me a parallel way using the global counter
  // as an implicit worklist. That is, every thread
  // should get its index from incrementing the counter
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

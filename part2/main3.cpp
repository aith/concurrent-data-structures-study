#include <thread>
#include <atomic>
#include "util.h"
#include "IOQueue.h"

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);
void parallel_enq(int size, int tid, int num_threads) {
  // Use this function to equeue indexes to each of the local
  // workstealing queues
}


void parallel_pow(float * result, int *power, int size, int tid, int num_threads) {
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed
}

int main() {
  float* result_parallel = new float[SIZE];
  int* power = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    result_parallel[i] = i;
  }
  linear_work(power, SIZE);

  // Launch NUM_THREADS threads to intialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.

  // Next, launch the parallel function that performs the parallel_pow
  // function from main1.cpp and main2.cpp but using workstealing
  
}

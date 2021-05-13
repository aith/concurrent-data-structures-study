#include <thread>
#include <atomic>
#include "vector"
#include "util.h"
#include "IOQueue.h"
#include "random"
#include "algorithm"
#include "set"
#include "iostream"

using namespace std;

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);
set <int> unfinished_threads;  // an array of tids

bool do_work(float* result, int tid, int* power, int chunk_size, int start) {
    if (Q[tid].deq_32(&power[start]) == 1) return false;  // get the new values
    for (int i=start; i<start+chunk_size; ++i) {
        for (int w = 0; w < power[i] - 1; w++) {
            result[i] = result[i] * result[i];
        }
    }
    return true;
}

void parallel_enq(int size, int tid, int num_threads) {
    // Use this function to equeue indexes to each of the local
    // workstealing queues
    int chunk_size = size / num_threads;
    int start = chunk_size * tid;
    Q[tid].init(chunk_size);
    for(int i = 0; i < chunk_size; ++i){
        Q[tid].enq(start+i);
    }
}

void parallel_pow(float *result, int *power, int size, int tid, int num_threads) {
    // Implement me using a workstealing approach.
    // You should use the Q IOQueues to compute
    // local work and then try to steal work
    // from others until all the work is completed

    // Unlike in main3.cpp, you should deq 32 elements
    // at a time.
    int chunk_size = size / num_threads;
    int start = chunk_size * tid;

    while(do_work(result,tid,power, chunk_size, start));
    unfinished_threads.erase(tid);
    atomic_fetch_add(&finished_threads, 1);
    while(finished_threads.load() < NUM_THREADS) {
        int new_tid = *(unfinished_threads.cbegin());  // for the picking algorithm, I just choose linearly
        start = chunk_size * new_tid;
        while(do_work(result,new_tid,power,chunk_size,start));
    }
}

int main() {

    vector <thread> threads;
    float *result_parallel = new float[SIZE];
    int *power = new int[SIZE];
    for (int i = 0; i < SIZE; i++) {
        result_parallel[i] = i;
    }
    linear_work(power, SIZE);

    // Launch NUM_THREADS threads to intialize the IOQueues in Q with
    // the indexes for each thread. Remember to initialize the Queues
    // with the size that they will need. Join the threads afterwards.

    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(parallel_enq, SIZE, i, NUM_THREADS));
    }

    for (thread &thr : threads) {
        thr.join();
    }
    threads.clear();

    // Next, launch the parallel function that performs the parallel_pow
    // function from main1.cpp and main2.cpp but using workstealing

    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(parallel_pow, result_parallel, power, SIZE, i, NUM_THREADS));
        unfinished_threads.insert(i);
    }

    for (thread &thr : threads) {
        thr.join();
    }
}

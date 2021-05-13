#include <thread>
#include "util.h"
#include "vector"

using namespace std;

void parallel_pow(float *result, int *power, int size, int tid, int num_threads) {
    // write me in a SPMD parallel way!  partition the data using
    // "chunks" rather than strides.  That is thread 0 computes elements
    // 0 through size/num_threads.  thread 1 computes elements
    // size/num_threads through 2*(size/num_threads)
    int chunk_size = size / num_threads;
    int start = chunk_size * tid;
    int end = start + chunk_size;
//    cout << start << " " << end << endl;
    for (int i = start; i < end; i++) {
        for (int w = 0; w < power[i] - 1; w++) {
            result[i] = result[i] * result[i];
        }
    }
}

int main() {
    vector<thread> threads;
    float *result_parallel = new float[SIZE];
    int *power = new int[SIZE];
    for (int i = 0; i < SIZE; i++) {
        result_parallel[i] = i;
    }
    linear_work(power, SIZE);

    // Launch NUM_THREADS threads and then join them
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(parallel_pow, result_parallel, power, SIZE, i, NUM_THREADS));
    }
    for(auto& thr : threads) {
        thr.join();
    }
}

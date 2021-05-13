#include <math.h>
#include <thread>
#include <atomic>
#include "CQueue.h"

#define SIZE (1024 * 1024 * 8)

CQueue memory_to_trig;
CQueue trig_to_memory;

void memory_thread_func(float *a, int size) {
    for (int i = 0; i < size; i += 8) {
        memory_to_trig.enq_8(a);
        trig_to_memory.deq_8(a);
    }
}

void trig_thread_func(int size) {

    for (int i = 0; i < size; i += 8) {
        float consume[8];
        memory_to_trig.deq_8(consume);
        for (int j = 0; j < 8; j++) {
            consume[j] = cos(consume[j]);
        }
        trig_to_memory.enq_8(consume);
    }
}

int main() {
    float *a = new float[SIZE];
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0.5 + i;
    }
    std::thread memory_thread(memory_thread_func, a, SIZE);
    std::thread trig_thread(trig_thread_func, SIZE);

    memory_thread.join();
    trig_thread.join();

    return 0;
}

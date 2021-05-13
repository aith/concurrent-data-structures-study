#include <atomic>

#define CQUEUE_SIZE 2048

using namespace std;

class CQueue {
public:

    CQueue() {
        head.store(0);
        tail.store(0);
        flag.store(true);
    }

    void enq(float e) {
        bool acquired = false;
        while (!acquired) {
            acquired = true;
            while ((head.load() + 1) % CQUEUE_SIZE == tail.load() % CQUEUE_SIZE);
            acquired = atomic_compare_exchange_weak(&flag, acquired, false);
        }
        int reserved_index = atomic_fetch_add(&head,1) % CQUEUE_SIZE;
        buffer[reserved_index] = e;
        flag.store(true);
    }

    void enq_8(float e[8]) {
        while ((head.load() + 8) % CQUEUE_SIZE == tail.load() % CQUEUE_SIZE);  // Spin while full. This must go first
        for (int i = 0; i < 8; i++) {
            this->enq(e[i]);
        }
    }


    float deq() {
        while (this->size() == 0);  // Spin while empty
        int reserved_index = atomic_fetch_add(&tail,1) % CQUEUE_SIZE;
        return buffer[reserved_index];
    }

    void deq_8(float e[8]) {
        while (head.load() % CQUEUE_SIZE == tail.load() % CQUEUE_SIZE);  // Spin while full. This must go first
        for (int i = 0; i < 8; i++) {
            e[i] = this->deq();
        }
    }


    int size() {
        return head.load() - tail.load();
    }

private:
    float buffer[CQUEUE_SIZE];  // circular bounded buffer
    atomic<int> head;
    atomic<int> tail;
    atomic<bool> flag;
};

#include <atomic>
#include "iostream"

class IOQueue {
public:
    IOQueue() {
    }


    // Use this function to initialize the queue to
    // the size that you need.
    void init(int size) {
        a = new int[size];
        s = size;
    }

    // enqueue the element e into the queue
    void enq(int e) {
        int index = std::atomic_fetch_add(&head, 1);
        a[index] = e;
    }

    // return a value from the queue.
    // return -1 if there is no more values
    // from the queue.
    int deq() {
        int index = std::atomic_fetch_add(&tail, 1);
        if (index > s) return -1;
        return a[index];
    }

    // return 32 values from the queue. The
    // values should be returned through
    // the array passed in.
    // return 0 if successful. return 1 if not
    // i.e. if the queue does not have 32 elements
    int deq_32(int ret[32]) {
        if (head.load() - tail.load() < 32) return 1;
        for (int i = 0;i<32;++i){
            int status = this->deq();
//            if (status == -1) return 1;
            ret[i] = status;
        }
        return 0;
    }

private:
    int *a;
    int s;
    std::atomic<int> head;
    std::atomic<int> tail;
};

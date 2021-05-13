#include <atomic>
#include <stdlib.h>

//#define SIZE 1024 * 1024 * 8

class CQueue {
 public:

  CQueue() {
  }

  void enq(float e) {
    std::atomic_store(&box, e);
    std::atomic_store(&flag, true);
  }

  float deq() {
      bool expected = true;
      while (std::atomic_compare_exchange_weak(&flag, &expected, false)) {
          expected = true;
      };
      float result = std::atomic_load(&box);
      std::atomic_store(&flag, false);
      return result;
  }
  
 private:
  std::atomic<float> box;
  std::atomic<bool> flag;
};

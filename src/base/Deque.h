#ifndef __BASE_DEQUE_H__
#define __BASE_DEQUE_H__

#include "Common.h"

/*
 * Implements doubly ended queue of elements of type T, backed by circular
 * array of N elements (less than 255). 
 *
 * [ E1; E2; E3; ...; En ]
 *   ^                ^
 *   front            back
 */
template <typename T, uint8_t N>
class Deque {
  private:
    uint8_t head, size;
    T array[N];

    inline uint8_t tail() {
      uint8_t tail = head + size;
      return (tail < N) ? tail : (tail - N);
    }

  public:
    Deque() : head(0), size(0) {};

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == N; }

    bool pushBack(const T& element) {
      if (isFull())
        return false;
      /* advance back => increment size */
      size++;
      /* put the element */
      array[tail()] = element;
      return true;
    }

    bool pushFront(const T& element) {
      if (isFull())
        return false;
      /* retreat front => decrement head */
      head = (head > 0) ? (head - 1) : (N - 1);
      size++;
      /* put the element */
      array[head] = element;
      return true;
    }

    bool popBack(T &element) {
      if (isEmpty())
        return false;
      /* get the element */
      element = array[head];
      /* advance front => decrement head */
      head = (head > 0) ? (head - 1) : (N - 1);
      size--;
      return true;
    }

    bool popFront(T &element) {
      if (isEmpty())
        return false;
      /* get the element */
      element = array[tail()];
      /* retreat back => decrement size */
      size--;
      return true;
    }

    bool front(T &element) {
      if (isEmpty())
        return false;
      element = array[head];
      return true;
    }

    bool back(T &element) {
      if (isEmpty())
        return false;
      element = array[tail()];
      return true;
    }
};

#endif

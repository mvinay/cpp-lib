#ifndef CPP_STACK_H
#define CPP_STACK_H

#include "lists/LinkedList.h"

namespace ds {

/*
   A LinkedList based implementation of Queue.
*/
template <class T> class Queue {
private:
  LinkedList<T> list;

public:
  Queue() {}

  inline unsigned int size() { return list.size(); }

  inline bool empty() { return list.empty(); }

  inline void clear() { list.clear(); }

  // Pop the first element.
  inline virtual T pop() { return list.pop(); }

  // Push the element at the end of queue.
  inline virtual void push(const T &item) { list.push_back(item); }

  // Get the next element to be dequeue-ed
  inline virtual T peek() { return list.front(); }
};
}
#endif

#ifndef CPP_STACK_H
#define CPP_STACK_H

#include "lists/LinkedList.h"

namespace ds {
/*
A LinkedList based implementation of Stack.
*/
template <class T> class Stack {
private:
  LinkedList<T> list;

public:
  Stack() {}

  inline unsigned int size() { return list.size(); }

  inline bool empty() { return list.empty(); }

  inline void clear() { list.clear(); }

  // Pop the element.
  inline virtual T pop() { return list.pop(); }

  // Push the element.
  inline virtual void push(const T &item) { list.prepend(item); }

  // Get the top element.
  inline virtual T peek() { return list.front(); }
};
}
#endif

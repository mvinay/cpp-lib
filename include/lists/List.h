#ifndef CPP_LIST_H
#define CPP_LIST_H

#include "common/Error.h"
#include "common/Utils.h"

namespace ds {

template <class T, class Comparator = utils::compare> class List {
protected:
  Comparator comparator;
  unsigned int _size;

  void checkIndex(int index, bool isInsert = false) {
    if ((index < 0) || (index > _size) || (index == _size && !isInsert))
      throw std::out_of_range("Array Index Out of Bounds: " +
                              std::to_string(index));
  }

public:
  List() : _size(0) {}

  inline unsigned int size() { return _size; }

  inline bool empty() { return (_size == 0); }

  inline void clear() { _size = 0; }

  // Get the ith element.
  virtual T at(int index) = 0;

  // Insert the element at the given postition.
  virtual void insert(const T &item, int index) = 0;

  // Delete the element at the given index.
  virtual T deleteAt(int index) = 0;

  // Remove the first element in the front.
  inline virtual T pop() { return deleteAt(0); }

  // Append the first element in the front.
  inline virtual void prepend(const T &item) { return insert(item, 0); }

  // Push the element to the last.
  inline virtual void push_back(const T &item) { insert(item, size()); }

  // Push the element to the last.
  inline virtual T pop_back() { return deleteAt(size() - 1); }

  // Get the front element.
  inline virtual T front() { return at(0); }

  // Get the last element.
  inline virtual T back() { return at(size() - 1); }

  virtual void reverse() = 0;

  // Basic implementation. Every derived class
  // should try to optimize it.
  virtual void remove(const T &item) {

    for (int i = 0; i < size(); ++i) {
      if (utils::equals(comparator, at(i), item)) {
        deleteAt(i);
        --i;
      }
    }
  }

  // Basic implementation. Every derived class
  // should try to optimize it.
  virtual int find(const T &item) {
    for (int i = 0; i < size(); ++i) {
      if (utils::equals(comparator, at(i), item))
        return i;
    }

    return INVALID_INDEX;
  }

  // Overloading the [] operator.
  virtual T &operator[](int index) = 0;

  virtual void print(std::ostream &OS) {
    OS << "{ ";
    for (int i = 0; i < size() - 1; ++i) {
      OS << at(i) << ", ";
    }
    OS << at(size() - 1) << " }";
  }
};
}
#endif

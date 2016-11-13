#ifndef CPP_LIST_H
#define CPP_LIST_H

#include "common/Error.h"
#include "common/Utils.h"

namespace ds {

template <class T> class List {
protected:
  unsigned int _size;

  void checkIndex(int index, bool isInsert = false) {
    if ((index < 0) || (index > _size) || (index == _size && !isInsert))
      throw std::out_of_range("Array Index Out of Bounds: " +
                              std::to_string(index));
  }

  virtual void clearData() = 0;

public:
  List() : _size(0) {}

  virtual ~List() {}

  inline unsigned int size() { return _size; }

  inline bool empty() { return (_size == 0); }

  inline void clear() {
    clearData();
    _size = 0;
  }

  // Get the ith element.
  virtual const T &at(int index) = 0;

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

  // Overloading the [] operator.
  const T &operator[](int index) {
    this->checkIndex(index);
    return at(index);
  }
};
}
#endif

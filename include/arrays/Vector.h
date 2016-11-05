#ifndef ARRAYS_VECTOR_H
#define ARRAYS_VECTOR_H

#include "common/Error.h"
#include "common/Utils.h"

#include <cassert>
#include <iostream>
#include <memory>

namespace ds {

template <class T, class Comparator = utils::compare> class Vector {
private:
  std::unique_ptr<T[]> data;
  Comparator comparator;
  unsigned int _size;
  unsigned int _capacity;

  // Increase the array size by 2.
  static const unsigned int increaseRate = 2;

  // Increase the array size if capacity * increaseThreshold < size;
  static constexpr float increaseThreshold = 1.75f;

  // Decrease the array size by half.
  static const unsigned int decreaseRate = 2;

  // Increase the array size if capacity * increaseThreshold > size;
  // NOTE: decreaseThreshold should always be less than the decreaseRate!
  static constexpr float decreaseThreshold = 0.25f;

  static const unsigned int initCapacity = 10;

  void increaseCapacity() {
    if (_size < increaseThreshold * _capacity)
      return;

    resize(_capacity * increaseRate);
  }

  void decreaseCapacity() {
    if (_size > decreaseThreshold * _capacity)
      return;

    resize(_capacity / decreaseRate);
  }

  void checkIndex(int index) {
    if (index < 0 || index >= _size) {
      throw std::out_of_range("Array Index Out of Bounds: " + std::to_string(index));
    }
  }

public:
  Vector() {
    _size = 0;
    // Re-size the array to 10 as default.
    resize(initCapacity);
  }

  Vector(int capacity) {
    _size = 0;
    resize(capacity);
  }

  inline unsigned int size() { return _size; }

  inline unsigned int capacity() { return _capacity; }

  bool empty() { return (_size == 0); }

  // Remove the element at index 0.
  T pop() { return deleteAt(0); }

  void prepend(const T &item) { insert(item, 0); }

  T at(int index) {
    checkIndex(index);
    return data[index];
  }

  void push_back(T item) {
    data[_size] = item;
    _size++;

    increaseCapacity();
  }

  void insert(const T &item, int index) {

    if (index == 0 && _size == 0) {
      data[0] = item;
      _size++;
      return;
    }

    checkIndex(index);

    // Move all the elements from @index to one step right till size-1.
    for (int i = _size - 1; i >= index; --i) {
      data[i + 1] = data[i];
    }

    data[index] = item;
    _size++;

    increaseCapacity();
  }

  T deleteAt(int index) {
    checkIndex(index);

    T ele = data[index];

    for (int i = index; i < _size - 1; ++i)
      data[i] = data[i + 1];

    _size--;
    decreaseCapacity();
    return ele;
  }

  void remove(const T &item) {

    for (int i = 0; i < _size; ++i) {
      if (utils::equals(comparator, data[i], item)) {
        deleteAt(i);
        --i;
      }
    }
  }

  int find(const T &item) {
    for (int i = 0; i < _size; ++i) {
      if (utils::equals(comparator, data[i], item))
        return i;
    }

    return -1;
  }

  void resize(unsigned int newCapacity) {
    if (newCapacity < _size) {
      throw std::invalid_argument("new capacity should not delete existing elements");
    }

    std::unique_ptr<int[]> new_data(new T[newCapacity]);

    if (_size != 0) {
      for (int i = 0; i < _size; ++i)
        new_data[i] = data[i];
    }

    data = std::move(new_data);
    _capacity = newCapacity;
  }

  // Overloading the [] operator.
  T &operator[](int index) {
    checkIndex(index);
    return data[index];
  }
};
}
#endif

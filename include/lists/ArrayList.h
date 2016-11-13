#ifndef ARRAYS_LIST_H
#define ARRAYS_LIST_H

#include "List.h"
#include "common/Error.h"

#include <memory>

namespace ds {

template <class T> class ArrayList : public List<T> {
private:
  T *data;
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
    if (this->_size < increaseThreshold * _capacity)
      return;

    resize(_capacity * increaseRate);
  }

  void decreaseCapacity() {
    if (this->_size > decreaseThreshold * _capacity)
      return;

    resize(_capacity / decreaseRate);
  }

protected:
  void clearData() {}

public:
  typedef T *iterator;

  iterator begin() { return &data[0]; }

  iterator end() { return (begin() + this->_size); }

  typedef const T *const_iterator;

  const_iterator begin() const { return &data[0]; }

  const_iterator end() const { return (begin() + this->_size); }

  ArrayList() : List<T>() {
    // Re-size the array to 10 as default.
    resize(initCapacity);
  }

  ~ArrayList() { delete[] data; }

  ArrayList(int capacity) : List<T>() { resize(capacity, true); }

  inline unsigned int capacity() { return _capacity; }

  const T &at(int index) {
    this->checkIndex(index);
    return data[index];
  }

  void insert(const T &item, int index) {

    this->checkIndex(index, true);

    // Move all the elements from @index to one step right till size-1.
    for (int i = this->_size - 1; i >= index; --i) {
      data[i + 1] = data[i];
    }

    data[index] = item;
    this->_size++;

    increaseCapacity();
  }

  T deleteAt(int index) {
    this->checkIndex(index);

    T ele = data[index];

    for (int i = index; i < this->_size - 1; ++i)
      data[i] = data[i + 1];

    this->_size--;
    decreaseCapacity();
    return ele;
  }

  void resize(unsigned int newCapacity, bool increaseSize = false) {
    if (newCapacity < this->_size) {
      throw std::invalid_argument(
          "new capacity should not delete existing elements");
    }

    T *new_data = new T[newCapacity];

    if (this->_size != 0) {
      for (int i = 0; i < this->_size; ++i)
        new_data[i] = data[i];
    }

    data = new_data;
    _capacity = newCapacity;
    if (increaseSize)
      this->_size = newCapacity;
  }

  // Overloading the [] operator.
  T &operator[](int index) {
    this->checkIndex(index);
    return data[index];
  }

  void reverse() {

    if (this->_size == 0 || this->_size == 1)
      return;

    unsigned int i = 0;
    unsigned int j = this->_size - 1;

    while (i < j) {
      std::swap(data[i], data[j]);
      i++;
      j--;
    }
  }
};
}
#endif

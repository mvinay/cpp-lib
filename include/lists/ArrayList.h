#ifndef ARRAYS_VECTOR_H
#define ARRAYS_VECTOR_H

#include "List.h"
#include "common/Error.h"

#include <memory>

namespace ds {

template <class T, class Comparator = utils::compare>
class ArrayList : public List<T, Comparator> {
private:
  std::unique_ptr<T[]> data;
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

public:
  ArrayList() : List<T, Comparator>() {
    // Re-size the array to 10 as default.
    resize(initCapacity);
  }

  ArrayList(int capacity) : List<T, Comparator>() { resize(capacity); }

  inline unsigned int capacity() { return _capacity; }

  T at(int index) {
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

  void resize(unsigned int newCapacity) {
    if (newCapacity < this->_size) {
      throw std::invalid_argument(
          "new capacity should not delete existing elements");
    }

    std::unique_ptr<T[]> new_data(new T[newCapacity]);

    if (this->_size != 0) {
      for (int i = 0; i < this->_size; ++i)
        new_data[i] = data[i];
    }

    data = std::move(new_data);
    _capacity = newCapacity;
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

#ifndef ARRAYS_VECTOR_H
#define ARRAYS_VECTOR_H
#include <memory>
class Vector {
private:
  std::unique_ptr<int[]> data;
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

  void increaseCapacity();

  void decreaseCapacity();

  void checkIndex(int index);

public:
  Vector();

  Vector(int capacity);

  inline unsigned int size() { return _size; }

  inline unsigned int capacity() { return _capacity; }

  bool empty() { return (_size == 0); }

  int at(int index);

  void push_back(int item);

  void insert(int item, int index);

  // Inserts as the index 0. Moving all others to right.
  // Special case of insert.
  void prepend(int item) { insert(item, 0); }

  // Delete at index. Move all the trailing elements left.
  int deleteAt(int index);

  // Remove the element at index 0.
  int pop() { return deleteAt(0); }

  // Remove all the items matching item.
  void remove(int item);

  // Returns the first index if found. -1 if not found.
  int find(int item);

  // On being 3/4th full, double the array size. If only quarter is filled,
  //  reduce the size by half.
  void resize(unsigned newCapacity);
};
#endif

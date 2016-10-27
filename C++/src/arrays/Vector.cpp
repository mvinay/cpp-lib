#include "arrays/Vector.h"
#include "common/Error.h"

#include <cassert>
#include <iostream>

Vector::Vector() {
  size = 0;
  // Re-size the array to 10 as default.
  resize(initCapacity);
}

Vector::Vector(int capacity) {
  size = 0;
  resize(capacity);
}

void Vector::increaseCapacity() {
  if (size < increaseThreshold * capacity)
    return;

  resize(capacity * increaseRate);
}

void Vector::decreaseCapacity() {
  if (size > decreaseThreshold * capacity)
    return;

  resize(capacity / decreaseRate);
}

void Vector::checkIndex(int index) {
  if (index < 0 || index >= size) {
    printError("Array Index Out of Bounds: " + std::to_string(index));
    exit(1);
  }
}

int Vector::at(unsigned int index) {
  checkIndex(index);
  return data[index];
}

void Vector::push(int item) {
  data[size] = item;
  size++;

  increaseCapacity();
}

void Vector::insert(int item, unsigned int index) {
  checkIndex(index);

  // Move all the elements from @index to one step right till size-1.
  for (int i = size - 1; i >= index; --i) {
    data[i + 1] = data[i];
  }

  data[index] = item;
  size++;

  increaseCapacity();
}

int Vector::deleteAt(unsigned int index) {
  checkIndex(index);

  int ele = data[index];

  for (int i = index; i < size - 1; ++i)
    data[i] = data[i + 1];

  size--;
  decreaseCapacity();
  return ele;
}

void Vector::remove(int item) {

  for (int i = 0; i < size; ++i) {
    if (data[i] == item) {
      deleteAt(i);
      --i;
    }
  }
}

int Vector::find(int item) {
  for (int i = 0; i < size; ++i) {
    if (data[i] == item)
      return i;
  }

  return -1;
}

void Vector::resize(unsigned int newCapacity) {
  assert(newCapacity < size && "new capacity should delete existing elements");

  std::unique_ptr<int[]> new_data(new int[newCapacity]);

  for (int i = 0; i < size; ++i)
    new_data[i] = data[i];

  data = std::move(new_data);
  capacity = newCapacity;
}

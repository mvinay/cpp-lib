#ifndef CPP_MAP_H
#define CPP_MAP_H

#include <functional>

namespace ds {

/*
   An interface for the Map.
*/
template <class K, class V> class Map {
protected:
  unsigned int _size;

public:
  Map() : _size(0) {}

  virtual ~Map(){};

  // Number of elements in the Map.
  inline unsigned int size() { return _size; }

  inline bool empty() { return (size() == 0); }

  // Empty all the elements.
  inline virtual void clear() = 0;

  // Search for the value for a given key.
  virtual V get(const K &key) = 0;

  // Remove the element with the key.
  virtual V remove(const K &key) = 0;

  // See whether the map has key.
  virtual bool contains(const K &key) = 0;

  // Add the given key-value pair.
  virtual void put(const K &key, const V &value) = 0;
};
}
#endif

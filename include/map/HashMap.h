#ifndef CPP_HASH_MAP_H
#define CPP_HASH_MAP_H

#include "lists/LinkedList.h"
#include "map/Map.h"

#include <cassert>
#include <tuple>

namespace ds {

/*
   An hash table based implementation for the Map. Uses Chaining to
   resolve the collisions.

   Uses std::hash as the default pre-hash function. User can over-ride with
   their
   own implementation. NOTE: This might affect the performance of hash map.

   For now, using a simple hash function which considers the last N significant
   bits
   to find the bucket. Where N is 2^N = tableSize;
   TODO: Improve the hash function. Example:  [ (ak + b) mod p] mod size
*/
template <class K, class V, class prehash = std::hash<K>>
class HashMap : public Map<K, V> {
private:
  // Table size will always be power of 2.
  static const unsigned int initTableSize = 16;
  unsigned int tableSize;

  typedef std::tuple<K, V> KeyValuePair;

  // TODO: ArrayList increases the size by default which makes it difficult
  // to use. Do one of the following.
  // 1. Create new Array DS
  // 2. Provide ArrayList of fixed size. (preferred).
  // FIXME: Bad way of doing things.
  LinkedList<KeyValuePair> *hashTable;

  unsigned int computeHash(const K &key) {
    return (prehash{}(key) & (tableSize - 1));
  }

public:
  HashMap(int _tableSize = initTableSize) : Map<K, V>() {
    hashTable = new LinkedList<KeyValuePair>[ _tableSize ];
    tableSize = _tableSize;
  }

  ~HashMap() {
    this->clear();
    delete[] hashTable;
  }

  virtual void clear() {
    for (unsigned i = 0; i < tableSize; ++i) {
      hashTable[i].clear();
    }
    this->_size = 0;
  }

  // Search for the value for a given key.
  virtual V get(const K &key){};

  // Remove the element with the key.
  virtual V remove(const K &key){};

  // See whether the map has key.
  virtual bool contains(const K &key){};

  // Add the given key-value pair.
  virtual void put(const K &key, const V &value) {
    // TODO: Over-write existing keys.
    unsigned int bucket = computeHash(key);
    assert(bucket >= 0 && bucket < tableSize);
    hashTable[bucket].push_back(KeyValuePair(key, value));
    this->_size++;
  };
};
}
#endif

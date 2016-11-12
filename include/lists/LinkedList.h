#ifndef ARRAYS_VECTOR_H
#define ARRAYS_VECTOR_H

#include "List.h"
#include "common/Error.h"

namespace ds {

/*
   A doubly linked list based implementation of the list.
*/
template <class T, class Comparator = utils::compare>
class LinkedList : public List<T, Comparator> {
private:
  struct Node {
    T data;
    Node *next, *prev;

    Node(T _data, Node *_next = nullptr, Node *_prev = nullptr)
        : data(_data), next(_next), prev(_prev) {}
  };
  typedef Node *NodePtr;

  NodePtr head, tail;

  NodePtr nodeAt(int index) {
    NodePtr temp = head;
    while (index > 0) {
      temp = temp->next;
      index--;
    }
    return temp;
  }

public:
  LinkedList() : List<T, Comparator>(), head(nullptr), tail(nullptr) {}

  const T &at(int index) {
    this->checkIndex(index);
    NodePtr node = nodeAt(index);
    return node->data;
  }

  void insert(const T &item, int index) {
    this->checkIndex(index, true);

    NodePtr newNode = new Node(item);

    // First node.
    if (index == 0) {
      if (this->_size == 0) {
        head = tail = newNode;
        this->_size++;
        return;
      }

      newNode->next = head;
      head->prev = newNode;
      head = newNode;
      this->_size++;
      return;
    }

    // Last node.
    if (index == this->_size) {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
      this->_size++;
      return;
    }

    // Any other node.
    NodePtr temp = nodeAt(index);
    NodePtr previous = temp->prev;

    newNode->prev = previous;
    newNode->next = temp;
    previous->next = newNode;
    temp->prev = newNode;
    this->_size++;
  }

  T deleteAt(int index) {
    this->checkIndex(index);
    NodePtr temp = nullptr;
    // First Node.
    if (index == 0) {
      temp = head;

      if (this->_size != 1) {
        head = head->next;
        head->prev = nullptr;
      } else {
        head = tail = nullptr;
      }

    } else if (index == this->_size - 1) {
      // Last Node.
      temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
    } else {
      // Any other node.
      temp = nodeAt(index);
      NodePtr previous = temp->prev;
      NodePtr nextNode = temp->next;
      previous->next = nextNode;
      nextNode->prev = previous;
    }

    T data = temp->data;
    delete temp;
    this->_size--;
    return data;
  }

  void reverse() {

    if (this->_size <= 1)
      return;

    NodePtr temp = head;
    while (temp != nullptr) {
      NodePtr curr = temp;
      temp = temp->next;
      std::swap(curr->next, curr->prev);
    }

    temp = head;
    head = tail;
    tail = temp;
  }
};
}
#endif

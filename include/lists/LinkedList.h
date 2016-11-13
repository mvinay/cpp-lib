#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "List.h"
#include "common/Error.h"

namespace ds {

/*
   A doubly linked list based implementation of the list.
*/
template <class T> class LinkedList : public List<T> {
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
    if (index == this->_size - 1)
      return tail;

    NodePtr temp = head;
    while (index > 0) {
      temp = temp->next;
      index--;
    }
    return temp;
  }

  T deleteNode(NodePtr node) {
    NodePtr prevNode = node->prev;
    NodePtr nextNode = node->next;

    if (prevNode) {
      prevNode->next = nextNode;
    }

    if (nextNode) {
      nextNode->prev = prevNode;
    }

    T data = node->data;
    delete node;
    return data;
  }

protected:
  void clearData() {
    NodePtr temp = head;
    while (temp) {
      NodePtr curr = temp;
      temp = temp->next;
      delete curr;
    }

    head = tail = nullptr;
  }

public:
  LinkedList() : List<T>(), head(nullptr), tail(nullptr) {}

  const T &at(int index) {
    this->checkIndex(index);
    NodePtr node = nodeAt(index);
    return node->data;
  }

  void insert(const T &item, int index) {
    this->checkIndex(index, true);
    NodePtr newNode = new Node(item);

    if (this->_size == 0) {
      head = tail = newNode;
      this->_size++;
      return;
    }

    if (this->_size == index) {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
      this->_size++;
      return;
    }

    NodePtr temp = nodeAt(index);
    NodePtr prevNode = temp->prev;
    if (prevNode) {
      prevNode->next = newNode;
      newNode->prev = prevNode;
    }

    temp->prev = newNode;
    newNode->next = temp;

    if (index == 0) {
      head = newNode;
    } else if (index == this->_size) {
      tail = newNode;
    }
    this->_size++;
  }

  T deleteAt(int index) {
    this->checkIndex(index);
    NodePtr temp = nodeAt(index);
    if (index == 0)
      head = head->next;
    else if (index == this->_size - 1)
      tail = tail->prev;
    T data = deleteNode(temp);
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
    std::swap(head, tail);
  }
};
}
#endif

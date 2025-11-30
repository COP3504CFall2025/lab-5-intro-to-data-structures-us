#pragma once
#include <assert.h>
#include <iostream>

template <typename T> class LinkedList {
  struct Node {
    T data;
    Node *next;
    Node *prev;
  };

public:
  // Behaviors
  void printForward() const {
    Node *current = head;
    while (current != nullptr) {
      std::cout << current->data << std::endl;
      current = current->next;
    }
  }
  void printReverse() const {
    Node *current = tail;
    while (current != nullptr) {
      std::cout << current->data << std::endl;
      current = current->prev;
    }
  }

  // Accessors
  [[nodiscard]] unsigned int getCount() const { return count; }
  Node *getHead() { return head; }
  const Node *getHead() const { return head; }
  Node *getTail() { return tail; }
  const Node *getTail() const { return tail; }

  // Insertion
  void addHead(const T &data) {
    Node *h = new Node;
    h->data = data;
    h->next = head;
    h->prev = nullptr;
    if (head)
      head->prev = h;
    else
      tail = h;
    head = h;
    count++;
  }
  void addTail(const T &data) {
    Node *t = new Node;
    t->data = data;
    t->next = nullptr;
    t->prev = tail;
    if (tail)
      tail->next = t;
    else
      head = t;
    tail = t;
    count++;
  }

  // Removal
  bool removeHead() {
    if (count <= 1) {
      return false;
    }
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    count--;
    return true;
  }
  bool removeTail() {
    if (count <= 1) {
      return false;
    }
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
    count--;
    return true;
  }
  void Clear() {
    while (count > 1) {
      removeHead();
    }
    if (head)
      count--;
    assert(head == tail);
    delete head;
    head = nullptr;
    tail = nullptr;
    assert(count == 0);
  }

  // Operators
  LinkedList<T> &operator=(LinkedList<T> &&other) noexcept {
    if (this == &other) {
      return this;
    }
    Clear();
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;

    return *this;
  }

  LinkedList<T> &operator=(const LinkedList<T> &rhs) {
    if (this == &rhs) {
      return *this;
    }
    Clear();
    Node *current = rhs.head;
    while (current != nullptr) {
      addTail(current->data);
      current = current->next;
    }
    return *this;
  }

  // Construction/Destruction
  LinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
  }

  LinkedList(const LinkedList<T> &list) {
    Node *current = list.head;
    while (current != nullptr) {
      addTail(current->data);
      current = current->next;
    }
  }
  LinkedList(LinkedList<T> &&other) noexcept {
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
  }
  ~LinkedList() { Clear(); }

private:
  // Stores pointers to first and last nodes and count
  Node *head;
  Node *tail;
  unsigned int count;
};

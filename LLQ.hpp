#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include <stdlib.h>

template <typename T> class LLQ : public QueueInterface<T> {
private:
  LinkedList<T> list;

public:
  // Constructor
  LLQ() = default;
  ~LLQ() = default;

  // Insertion
  void enqueue(const T &item) override { list.addTail(item); }

  // Deletion
  T dequeue() override {
    if (list.getCount > 0) {
      T val = list.getHead()->data;
      if (list.getCount() == 1)
        list.Clear();
      else
        list.removeHead();
      return val;
    } else {
      throw "empty linked list";
    }
  }

  // Access
  T peek() const override {
    if (list.getCount() > 0)
      list.getHead()->data;
    else
      throw "empty linked list";
  }

  // Getter
  std::size_t getSize() const noexcept override { return list.getCount(); }

  void PrintForward() { list.printForward(); }
  void PrintReverse() { list.printReverse(); }
};

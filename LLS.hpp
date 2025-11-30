#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>
#include <stdlib.h>

template <typename T> class LLS : public StackInterface<T> {
private:
  LinkedList<T> list;

public:
  // Constructor
  LLS() = default;

  // Insertion
  void push(const T &item) override { list.addHead(item); }

  // Deletion
  T pop() override {
    if (list.getCount() > 0) {
      T val = list.getHead()->data;
      if (list.getCount() == 1)
        list.clear();
      else
        list.removeHead();
      return val;
    } else {
      throw std::runtime_error("empty stack");
    }
  }

  // Access
  T peek() const override {
    if (list.getCount() > 0)
      return list.getHead()->data;
    else
      throw std::runtime_error("empty stack");
  }

  // Getters
  std::size_t getSize() const noexcept override { return list.getCount(); }

  void PrintForward() { list.printForward(); }
  void PrintReverse() { list.printReverse(); }
};

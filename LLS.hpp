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
  ~LLS() override = default;

  // Insertion
  void push(const T &item) override { list.addHead(item); }

  // Deletion
  T pop() override {
    if (list.getCount() > 0) {
      T val = list.getHead()->data;
      if (list.getCount() == 1)
        list.Clear();
      else
        list.removeHead();
      return val;
    } else {
      throw "empty array";
    }
  }

  // Access
  T peek() const override {
    if (list.getCount() > 0)
      return list.getTail()->data;
    else
      throw "empty array";
  }

  // Getters
  std::size_t getSize() const noexcept override { return list.getCount(); }

  void PrintForward() { list.printForward(); }
  void PrintReverse() { list.printReverse(); }
};

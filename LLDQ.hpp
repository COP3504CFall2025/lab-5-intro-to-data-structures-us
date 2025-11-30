#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class LLDQ : public DequeInterface<T> {
private:
  LinkedList<T> list;

public:
  // Constructor
  LLDQ() = default;
  ~LLDQ() = default;

  // Core Insertion Operations
  void pushFront(const T &item) override { list.addHead(item); }
  void pushBack(const T &item) override { list.addTail(item); }

  // Core Removal Operations
  T popFront() override {
    if (list.getCount() > 0) {
      T val = list.getHead()->data;
      if (list.getCount() == 1) {
        list.Clear();
      } else {
        list.removeHead();
      }
      return val;
    } else {
      throw "empty linked list";
    }
  }
  T popBack() override {
    if (list.getCount() > 0) {
      T val = list.getTail()->data;
      if (list.getCount() == 1) {
        list.Clear();
      } else {
        list.removeTail();
      }
      return val;
    } else {
      throw "empty linked list";
    }
  }

  // Element Accessors
  const T &front() const override {
    if (list.getCount() > 0)
      return list.getHead()->data;
    else
      throw "empty linked list";
  }
  const T &back() const override {
    if (list.getCount() > 0)
      return list.getTail()->data;
    else
      throw "empty linked list";
  }

  // Getter
  std::size_t getSize() const noexcept override { return list.getCount(); }

  void PrintForward() { list.printForward(); }
  void PrintReverse() { list.printReverse(); }
};

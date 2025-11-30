#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T> class ABS : public StackInterface<T> {
public:
  // Big 5 + Parameterized Constructor
  ABS() {
    array_ = new T[1];
    curr_size_ = 0;
    capacity_ = 1;
  }
  explicit ABS(const size_t capacity) {
    array_ = new T[capacity];
    curr_size_ = 0;
    capacity_ = capacity;
  }
  ABS(const ABS &other) {
    curr_size_ = other.curr_size_;
    capacity_ = other.capacity_;
    array_ = new T[capacity_];
    for (int i = 0; i < other.curr_size_; i++)
      *(array_ + i) = *(other.array_ + i);
  }
  ABS &operator=(const ABS &rhs) {
    if (this == &rhs)
      return *this;
    curr_size_ = rhs.curr_size_;
    capacity_ = rhs.capacity_;
    T *new_arr = new T[capacity_];
    for (int i = 0; i < rhs.curr_size_; i++)
      *(new_arr + i) = *(rhs.array_ + i);
    delete[] array_;
    array_ = new_arr;
    new_arr = nullptr;
    return *this;
  }
  ABS(ABS &&other) noexcept {
    curr_size_ = other.curr_size_;
    capacity_ = other.capacity_;
    array_ = other.array_;
    other.curr_size_ = 0;
    other.capacity_ = 0;
    other.array_ = nullptr;
  }
  ABS &operator=(ABS &&rhs) noexcept {
    if (this == &rhs)
      return *this;
    curr_size_ = rhs.curr_size_;
    capacity_ = rhs.capacity_;
    delete[] array_;
    array_ = rhs.array_;
    rhs.curr_size_ = 0;
    rhs.capacity_ = 0;
    rhs.array_ = nullptr;
  }
  ~ABS() noexcept override {
    delete[] array_;
    array_ = nullptr;
    curr_size_ = 0;
    capacity_ = 0;
  }

  // Get the number of items in the ABS
  [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

  // Get the max size of the ABS
  [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

  // Return underlying data for the stack
  [[nodiscard]] T *getData() const noexcept { return array_; }

  // Push item onto the stack
  void push(const T &data) override {
    if (curr_size_ == capacity_) {
      capacity_ *= scale_factor_;
      T *new_arr = new T[capacity_];
      for (int i = 0; i < curr_size_; i++)
        *(new_arr + i) = *(array_ + i);
      delete[] array_;
      array_ = new_arr;
      new_arr = nullptr;
    }
    *(array_ + curr_size_) = data;
    curr_size_++;
  }

  T peek() const override {
    if (curr_size_ > 0)
      return *(array_ + curr_size_ - 1);
    else
      throw "empty array";
  }

  T pop() override {
    if (curr_size_ > 0) {
      curr_size_--;
      return *(array_ + curr_size_);
    } else {
      throw "empty array";
    }
  }

  void PrintForward() {
    for (int i = 0; i < curr_size_; i++) {
      std::cout << *(array_ + i) << std::endl;
    }
  }
  void PrintReverse() {
    for (int i = curr_size_ - 1; i >= 0; i--) {
      std::cout << *(array_ + i) << std::endl;
    }
  }

private:
  size_t capacity_;
  size_t curr_size_;
  T *array_;
  static constexpr size_t scale_factor_ = 2;
};

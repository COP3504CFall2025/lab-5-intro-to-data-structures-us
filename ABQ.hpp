#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T> class ABQ : public QueueInterface<T> {
  size_t capacity_;
  size_t curr_size_;
  int front_;
  T *array_;
  static constexpr size_t scale_factor_ = 2;

public:
  // Constructors + Big 5
  ABQ() {
    array_ = new T[1];
    curr_size_ = 0;
    capacity_ = 1;
    front_ = 0;
  }
  explicit ABQ(const size_t capacity) {
    array_ = new T[capacity];
    curr_size_ = 0;
    front_ = 0;
    capacity_ = capacity;
  }
  ABQ(const ABQ &other) {
    curr_size_ = other.curr_size_;
    capacity_ = other.capacity_;
    front_ = other.front_;
    array_ = new T[capacity_];
    for (int i = 0; i < other.curr_size_; i++)
      *(array_ + i) = *(other.array_ + i);
  }
  ABQ &operator=(const ABQ &rhs) {
    if (this == &rhs)
      return *this;
    curr_size_ = rhs.curr_size_;
    capacity_ = rhs.capacity_;
    front_ = rhs.front_;
    T *new_arr = new T[capacity_];
    for (int i = 0; i < rhs.curr_size_; i++)
      *(new_arr + i) = *(rhs.array_ + i);
    delete[] array_;
    array_ = new_arr;
    new_arr = nullptr;
    return *this;
  }
  ABQ(ABQ &&other) noexcept {
    curr_size_ = other.curr_size_;
    capacity_ = other.capacity_;
    front_ = other.front_;
    array_ = other.array_;
    other.curr_size_ = 0;
    other.capacity_ = 0;
    other.array_ = nullptr;
  }
  ABQ &operator=(ABQ &&rhs) noexcept {
    if (this == &rhs)
      return *this;
    curr_size_ = rhs.curr_size_;
    capacity_ = rhs.capacity_;
    front_ = rhs.front_;
    delete[] array_;
    array_ = rhs.array_;
    rhs.curr_size_ = 0;
    rhs.capacity_ = 0;
    rhs.array_ = nullptr;
    return *this;
  }
  ~ABQ() noexcept override {
    delete[] array_;
    array_ = nullptr;
    curr_size_ = 0;
    capacity_ = 0;
    front_ = 0;
  }

  // Getters
  [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }
  [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }
  [[nodiscard]] T *getData() const noexcept { return array_; }

  // Insertion
  void enqueue(const T &data) override {
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

  // Access
  T peek() const override {
    if (curr_size_ > 0)
      return *(array_ + front_);
    else
      throw std::runtime_error("empty queue");
  }

  // Deletion
  T dequeue() override {
    if (curr_size_ == 0)
      throw std::runtime_error("empty queue");

    T val = *(array_ + front_);
    front_++;
    curr_size_--;

    if (curr_size_ * 2 <= capacity_) {
      capacity_ /= scale_factor_;
      if (capacity_ < 4)
        capacity_ = 4;
      T *new_arr = new T[capacity_];
      for (int i = 0; i < curr_size_; ++i)
        *(new_arr + i) = *(array_ + front_ + i);
      delete[] array_;
      array_ = nullptr;
      array_ = new_arr;
      front_ = 0;
    }
    return val;
  }

  void PrintForward() {
    for (int i = 0; i < curr_size_; i++) {
      std::cout << *(array_ + i) << std::endl;
    }
  }
  void PrintReverse() {
    for (int i = static_cast<int>(curr_size_) - 1; i >= 0; i--) {
      std::cout << *(array_ + i) << std::endl;
    }
  }
};

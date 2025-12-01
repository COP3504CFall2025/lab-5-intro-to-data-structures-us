#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class ABDQ : public DequeInterface<T> {
private:
  T *data_;              // underlying dynamic array
  std::size_t capacity_; // total allocated capacity
  std::size_t size_;     // number of stored elements
  std::size_t front_;    // index of front element
  std::size_t back_;     // index after the last element (circular)

  static constexpr std::size_t SCALE_FACTOR = 2;

public:
  // Big 5
  ABDQ() {
    data_ = new T[4];
    size_ = 0;
    capacity_ = 4;
    front_ = 0;
    back_ = size_;
  }
  explicit ABDQ(const size_t capacity) {
    data_ = new T[capacity];
    size_ = 0;
    front_ = 0;
    back_ = size_;
    capacity_ = capacity;
  }
  ABDQ(const ABDQ &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new T[capacity_];
    back_ = size_;
    int index = other.front_;
    for (int i = 0; i < other.size_; i++) {
      *(data_ + i) = *(other.data_ + index);
      index = (index + 1) % other.capacity_;
    }
    front_ = 0;
  }
  ABDQ &operator=(const ABDQ &rhs) {
    if (this == &rhs)
      return *this;
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    back_ = size_;
    T *new_arr = new T[capacity_];
    int index = rhs.front_;
    for (int i = 0; i < rhs.size_; i++) {
      *(new_arr + i) = *(rhs.data_ + index);
      index = (index + 1) % rhs.capacity_;
    }
    front_ = 0;
    delete[] data_;
    data_ = new_arr;
    new_arr = nullptr;
    return *this;
  }
  ABDQ(ABDQ &&other) noexcept {
    size_ = other.size_;
    capacity_ = other.capacity_;
    front_ = other.front_;
    back_ = other.back_;
    data_ = other.data_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.front_ = 0;
    other.back_ = 0;
    other.data_ = nullptr;
  }
  ABDQ &operator=(ABDQ &&rhs) noexcept {
    if (this == &rhs)
      return *this;
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    front_ = rhs.front_;
    back_ = rhs.size_;
    delete[] data_;
    data_ = rhs.data_;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.front_ = 0;
    rhs.back_ = 0;
    rhs.data_ = nullptr;
    return *this;
  }
  ~ABDQ() noexcept override {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    front_ = 0;
    back_ = size_;
  }

  // Insertion
  void pushFront(const T &item) override {
    if (size_ == capacity_)
      ensureCapacity();
    front_ = (front_ + capacity_ - 1) % capacity_;
    *(data_ + front_) = item;
    size_++;
    back_ = (front_ + size_) % capacity_;
  }
  void pushBack(const T &item) override {
    if (size_ == capacity_)
      ensureCapacity();
    back_ = (front_ + size_) % capacity_;
    *(data_ + back_) = item;
    size_++;
  }

  // Deletion
  T popFront() override {
    if (size_ == 0)
      throw std::runtime_error("empty deque");
    T val = *(data_ + front_);
    front_ = (front_ + 1 + capacity_) % capacity_;
    size_--;
    shrinkIfNeeded();
    return val;
  }
  T popBack() override {
    if (size_ == 0)
      throw std::runtime_error("empty deque");
    T val = *(data_ + back_);
    back_ = (back_ - 1 + capacity_) % capacity_;
    size_--;
    shrinkIfNeeded();
    return val;
  }

  // Access
  const T &front() const override {
    if (size_ == 0)
      throw std::runtime_error("empty deque");
    return *(data_ + front_);
  }
  const T &back() const override {
    if (size_ == 0)
      throw std::runtime_error("empty deque");
    return *(data_ + (back_ - 1 + capacity_) % capacity_);
  }

  // Getters
  std::size_t getSize() const noexcept override { return size_; }
  void PrintForward() {
    for (int i = 0; i < size_; i++) {
      std::cout << *(data_ + i) << std::endl;
    }
  }
  void PrintReverse() {
    for (int i = static_cast<int>(size_) - 1; i >= 0; i--) {
      std::cout << *(data_ + i) << std::endl;
    }
  }

  void ensureCapacity() {
    size_t old_capacity = capacity_;
    capacity_ *= SCALE_FACTOR;
    T *new_arr = new T[capacity_];
    size_t old_index = front_;
    size_t new_index = 0;
    while (new_index < size_) {
      *(new_arr + new_index) = *(data_ + old_index);
      new_index++;
      old_index = (old_index + 1) % old_capacity;
    }
    delete[] data_;
    data_ = new_arr;
    new_arr = nullptr;
    front_ = 0;
    back_ = size_;
  }

  void shrinkIfNeeded() {
    if (size_ * 2 > capacity_ || capacity_ <= 4) {
      return;
    }
    size_t old_capacity = capacity_;
    capacity_ /= SCALE_FACTOR;
    T *new_arr = new T[capacity_];
    size_t old_index = front_;
    size_t new_index = 0;
    while (new_index < size_) {
      *(new_arr + new_index) = *(data_ + old_index);
      new_index++;
      old_index = (old_index + 1) % old_capacity;
    }
    delete[] data_;
    data_ = new_arr;
    new_arr = nullptr;
    front_ = 0;
    back_ = size_;
  }
};

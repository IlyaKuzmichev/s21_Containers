#ifndef S21_CONTAINERS_SRC_S21_QUEUE_H_
#define S21_CONTAINERS_SRC_S21_QUEUE_H_

#include <utility>

#include "containers/s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  // Queue Member type
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using value_type = T;

  // Queue Member functions
  queue() : list_() {}
  queue(const queue &q) : list_(q.list_) {}
  queue(queue &&q) noexcept { std::swap(list_, q.list_); }
  queue<T> &operator=(queue &&q) noexcept {
    std::swap(list_, q.list_);
    return *this;
  }
  queue(std::initializer_list<value_type> const &items) : list_(items) {}
  ~queue() {}

  // Queue Element access
  const_reference front() const { return list_.front(); }
  const_reference back() const { return list_.back(); }

  // Queue Capacity
  bool empty() const { return list_.empty(); }
  size_type size() const { return list_.size(); }

  // Queue Modifiers
  void push(const_reference value) { list_.push_back(value); }
  void pop() { list_.pop_front(); }
  void swap(queue &other) noexcept { list_.swap(other.list_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    list_.insert_many_back(args...);
  }

 private:
  list<T> list_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_QUEUE_H_

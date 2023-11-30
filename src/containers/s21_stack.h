#ifndef S21_CONTAINERS_SRC_S21_STACK_H_
#define S21_CONTAINERS_SRC_S21_STACK_H_

#include <utility>

#include "containers/s21_list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  // Stack Member type
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using value_type = T;

  // Stack Member functions
  stack() : list_() {}
  stack(const stack &q) : list_(q.list_) {}
  stack(stack &&q) noexcept { std::swap(list_, q.list_); }
  stack<T> &operator=(stack &&q) noexcept {
    std::swap(list_, q.list_);
    return *this;
  }
  stack(std::initializer_list<value_type> const &items) : list_(items) {}
  ~stack() {}

  // Stack Element access
  const_reference top() const { return list_.back(); }

  // Stack Capacity
  bool empty() const { return list_.empty(); }
  size_type size() const { return list_.size(); }

  // Stack Modifiers
  void push(const_reference value) { list_.push_back(value); }
  void pop() { list_.pop_back(); }
  void swap(stack &other) noexcept { list_.swap(other.list_); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    list_.insert_many_back(args...);
  }

 private:
  list<T> list_;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_STACK_H_

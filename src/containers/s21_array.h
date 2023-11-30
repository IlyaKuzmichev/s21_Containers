#ifndef S21_CONTAINERS_SRC_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T, size_t N>
struct array {
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = value_type*;
  using const_iterator = const value_type*;
  using size_type = size_t;

  array() = default;
  array(std::initializer_list<value_type> init_list);
  array(const array& other);
  array(array&& other) noexcept;
  ~array() = default;

  array& operator=(array&& other) noexcept;
  array& operator=(array& other) noexcept;

  constexpr iterator begin() noexcept;
  constexpr const_iterator begin() const noexcept;
  constexpr iterator end() noexcept;
  constexpr const_iterator end() const noexcept;

  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  void swap(array& other);
  void fill(const_reference value);

  reference operator[](size_type pos) noexcept;
  constexpr const_reference front() const noexcept;
  constexpr const_reference back() const noexcept;

  value_type data_[N];
};

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> init_list) {
  if (init_list.size() != N) {
    throw std::invalid_argument(
        "Initializer list size doesn't match array size");
  }
  std::copy(init_list.begin(), init_list.end(), data_);
}

template <typename T, size_t N>
array<T, N>::array(array&& other) noexcept {
  std::move(other.begin(), other.end(), data_);
}

template <typename T, size_t N>
array<T, N>::array(const array& other) {
  std::copy(other.begin(), other.end(), data_);
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array&& other) noexcept {
  if (this != &other) {
    std::swap(data_, other.data_);
  }
  return *this;
}

template <typename T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::operator[](
    size_type pos) noexcept {
  return data_[pos];
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array& other) noexcept {
  if (this == &other) {
    return *this;
  }
  std::copy(other.data_, other.data_ + N, data_);
  return *this;
}

template <typename T, size_t N>
constexpr typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, size_t N>
constexpr typename array<T, N>::const_iterator array<T, N>::begin()
    const noexcept {
  return data_;
}

template <typename T, size_t N>
constexpr typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + N;
}

template <typename T, size_t N>
constexpr typename array<T, N>::const_iterator array<T, N>::end()
    const noexcept {
  return data_ + N;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("pos out of range");
  }
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("pos out of range");
  }
  return data_[pos];
}

template <typename T, size_t N>
constexpr bool array<T, N>::empty() const noexcept {
  return N == 0;  // В этом месте проверяется размер массива N
}

template <typename T, size_t N>
constexpr typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

template <typename T, size_t N>
constexpr typename array<T, N>::size_type array<T, N>::max_size()
    const noexcept {
  return N;
}

template <typename T, size_t N>
void array<T, N>::swap(array& other) {
  std::swap_ranges(begin(), end(), other.begin());
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(begin(), end(), value);
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_ARRAY_H_

#ifndef S21_CONTAINERS_SRC_S21_SET_H_
#define S21_CONTAINERS_SRC_S21_SET_H_

#include <iostream>
#include <tuple>
#include <utility>

#include "containers/s21_multiset.h"
#include "containers/s21_vector.h"

namespace s21 {

template <typename Key>
class set : public multiset<Key> {
 public:
  using Base = multiset<Key>;
  using Grandbase = RBTree<Key, decltype(std::ignore), false>;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  using iterator = typename Base::iterator;
  using const_iterator = iterator;
  using Base::Base;

  set(std::initializer_list<value_type> const& items) {
    for (const value_type& item : items) {
      this->insert(item);
    }
  }

  const_iterator begin() const noexcept { return iterator(Base::begin()); }

  const_iterator end() const noexcept { return iterator(Base::end()); }

  iterator find(key_type key) noexcept { return iterator(Base::find(key)); }

  void swap(set& other) { Base::swap(other); }

  std::pair<iterator, bool> insert(const value_type& value) {
    iterator existing = this->find(value);
    if (existing != this->end()) {
      return std::pair<iterator, bool>{existing, false};
    }
    return std::pair<iterator, bool>{Base::insert(value), true};
  }

  void merge(set& other) { Grandbase::merge(other); }

  bool contains(const value_type& value) { return find(value) != end(); }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back(insert(std::forward<value_type>(args))), ...);
    return result;
  }

 private:
  using Base::count;
  using Base::equal_range;
  using Base::lower_bound;
  using Base::upper_bound;
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_SET_H_

#ifndef S21_CONTAINERS_SRC_S21_MULTISET_H_
#define S21_CONTAINERS_SRC_S21_MULTISET_H_

#include <iostream>
#include <tuple>
#include <utility>

#include "containers/s21_vector.h"
#include "redblacktree/s21_rbtree.h"

namespace s21 {

template <typename Key>
class multiset : public RBTree<Key, decltype(std::ignore), false> {
 public:
  using Base = RBTree<Key, decltype(std::ignore), false>;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class MultiSetIterator : public Base::const_iterator {
   public:
    using iterator_base = typename Base::const_iterator;
    using iterator_base::iterator_base;
    MultiSetIterator() = default;
    explicit MultiSetIterator(const iterator_base& it) : iterator_base{it} {}
    MultiSetIterator& operator=(const MultiSetIterator&) = default;
    const_reference operator*() const { return this->current_->data.first; }
  };

  using iterator = MultiSetIterator;
  using const_iterator = iterator;
  using Base::RBTree;

  multiset(std::initializer_list<value_type> const& items) {
    for (const value_type& item : items) {
      insert(item);
    }
  }

  const_iterator begin() const noexcept { return iterator(Base::begin()); }

  const_iterator end() const noexcept { return iterator(Base::end()); }

  iterator find(const Key& key) noexcept {
    iterator it = this->lower_bound(key);
    if (it == end() || *it != key) {
      return end();
    }
    return it;
  }

  iterator insert(const_reference value) {
    return Base::insert(std::make_pair(value, std::ignore)).first;
  }

  void swap(multiset& other) noexcept { Base::swap(other); }

  void merge(multiset& other) noexcept { Base::merge(other); }

  size_type count(const key_type& key) noexcept {
    size_t res = 0;
    auto lb = this->lower_bound(key);
    auto ub = this->upper_bound(key);
    for (auto iter = lb; iter != ub; ++iter) {
      res++;
    }
    return res;
  }

  void erase(iterator pos) { Base::erase(pos); }

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return std::make_pair(this->lower_bound(key), this->upper_bound(key));
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back({insert(std::forward<value_type>(args)), true}), ...);
    return result;
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_MULTISET_H_

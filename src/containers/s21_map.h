#ifndef S21_CONTAINERS_SRC_S21_MAP_H_
#define S21_CONTAINERS_SRC_S21_MAP_H_

#include <utility>

#include "containers/s21_vector.h"
#include "redblacktree/s21_rbtree.h"

namespace s21 {
template <typename Key, typename T>
class map : public RBTree<Key, T, true> {
 public:
  // Map Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using const_iterator = typename RBTree<Key, T, true>::const_iterator;
  using iterator = typename RBTree<Key, T, true>::iterator;

  using Base = RBTree<Key, T, true>;

  using Base::Base;

  // Map Element access
  mapped_type& at(const key_type& key) {
    iterator tmp = this->find(key);
    if (tmp == this->end()) {
      throw std::out_of_range(
          "Container does not have an element with the specified key");
    }
    return (*tmp).second;
  }

  mapped_type& operator[](const key_type& key) {
    iterator tmp = this->find(key);
    if (tmp == this->end()) {
      mapped_type zero_value;
      tmp = Base::insert(std::make_pair(key, zero_value)).first;
    }
    return (*tmp).second;
  }

  // Map Modifiers

  void swap(map& other) noexcept { Base::swap(other); }

  void merge(map& other) noexcept { Base::merge(other); }

  std::pair<iterator, bool> insert(const value_type& value) {
    return Base::insert(value);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return Base::insert(std::pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    iterator tmp = this->find(key);
    if (tmp == this->end()) {
      return Base::insert(std::pair(key, obj));
    }
    (*tmp).second = obj;
    return std::make_pair(tmp, true);
  }

  // Bonus
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> result;

    (result.push_back(Base::insert(std::forward<value_type>(args))), ...);
    return result;
  }

 private:
  using Base::lower_bound;
  using Base::upper_bound;
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_MAP_H_

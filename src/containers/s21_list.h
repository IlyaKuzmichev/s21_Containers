#ifndef S21_CONTAINERS_SRC_S21_LIST_H_
#define S21_CONTAINERS_SRC_S21_LIST_H_

#include <cstddef>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l) noexcept;
  ~list();

  list& operator=(const list& l);
  list& operator=(list&& l) noexcept;
  list& operator=(std::initializer_list<value_type> const& items);

  const_reference front() const;
  const_reference back() const;

  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  class Node;

  Node* head_;
  Node* tail_;
  size_type size_;

  void DestroyAllNodes();
  Node* Extract(iterator pos);
  Node* Extract(Node* node);
  void Erase(Node* node);
  iterator Insert(iterator pos, Node* node);
  list Divide();
};

template <typename T>
list<T>::list() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
  size_ = n;
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
  for (auto iter = l.cbegin(); iter != l.cend(); ++iter) {
    push_back(*iter);
  }
}

template <typename T>
list<T>::list(list&& l) noexcept {
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;

  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  DestroyAllNodes();
}

template <typename T>
list<T>& list<T>::operator=(const list& l) {
  if (this == &l) {
    return *this;
  }

  DestroyAllNodes();
  for (auto iter = l.cbegin(); iter != l.cend(); ++iter) {
    push_back(*iter);
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& l) noexcept {
  if (this == &l) {
    return *this;
  }

  DestroyAllNodes();

  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;

  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(std::initializer_list<value_type> const& items) {
  DestroyAllNodes();
  for (auto item : items) {
    push_back(item);
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return head_->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return tail_->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return ListIterator(this, head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
  return ListConstIterator(this, head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return ListIterator(this, nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
  return ListConstIterator(this, nullptr);
}

template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename T>
void list<T>::clear() {
  DestroyAllNodes();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (size_ == 0) {
    push_back(value);
    return begin();
  }

  Node* inserted = new Node(value);
  pos.InsertBefore(inserted);

  if (pos == begin()) {
    head_ = inserted;
  } else if (pos == end()) {
    tail_ = inserted;
  }

  ++size_;
  return ListIterator(this, inserted);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Erase(pos.current_);
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* node = new Node(tail_, nullptr, value);
  if (empty()) {
    head_ = node;
  }
  tail_ = node;
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  Erase(tail_);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* node = new Node(nullptr, head_, value);
  if (empty()) {
    tail_ = node;
  }
  head_ = node;
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  Erase(head_);
}

template <typename T>
void list<T>::swap(list<T>& other) {
  std::swap(*this, other);
}

template <typename T>
void list<T>::merge(list<T>& other) {
  if (this == &other) {
    return;
  }

  auto iter = begin();

  while (other.size() > 0) {
    if (iter == end() || *iter > other.front()) {
      auto node = other.Extract(other.head_);
      iter = Insert(iter, node);
    } else {
      ++iter;
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  auto iter = ListIterator(this, pos.current_);
  while (other.size() > 0) {
    auto node = other.Extract(other.head_);
    Insert(iter, node);
  }
}

template <typename T>
void list<T>::reverse() {
  Node* current = head_;
  while (current != nullptr) {
    std::swap(current->prev, current->next);
    current = current->prev;
  }
  std::swap(head_, tail_);
}

template <typename T>
void list<T>::unique() {
  if (size_ < 2) {
    return;
  }

  auto iter = begin();
  ++iter;

  for (; iter != end(); ++iter) {
    iterator prev(iter);
    --prev;

    if (*iter == *prev) {
      Erase(prev.current_);
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) {
    return;
  }

  list<T> second_half = Divide();

  sort();
  second_half.sort();

  merge(second_half);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  auto iter = ListIterator(this, pos.current_);

  if constexpr (sizeof...(args) > 0) {
    (insert(iter, value_type(std::forward<Args>(args))), ...);
    for (size_type i = 0; i < sizeof...(args); ++i) {
      --iter;
    }
  }

  return iter;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  (push_back(value_type(std::forward<Args>(args))), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  insert_many(begin(), args...);
}

template <typename T>
void list<T>::DestroyAllNodes() {
  Node* current = head_;
  Node* next = nullptr;

  while (current != nullptr) {
    next = current->next;
    delete current;
    current = next;
  }

  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
typename list<T>::Node* list<T>::Extract(iterator pos) {
  return Extract(pos.current_);
}

template <typename T>
typename list<T>::Node* list<T>::Extract(Node* node) {
  if (node == head_) {
    head_ = head_->next;
  }

  if (node == tail_) {
    tail_ = tail_->prev;
  }

  if (node->prev != nullptr) {
    node->prev->next = node->next;
  }

  if (node->next != nullptr) {
    node->next->prev = node->prev;
  }

  node->prev = nullptr;
  node->next = nullptr;

  --size_;

  return node;
}

template <typename T>
void list<T>::Erase(Node* node) {
  Node* erased = Extract(node);

  delete erased;
}

template <typename T>
typename list<T>::iterator list<T>::Insert(iterator pos, Node* node) {
  if (size_ == 0) {
    head_ = node;
    tail_ = node;
    ++size_;
    return begin();
  }

  pos.InsertBefore(node);

  if (pos == begin()) {
    head_ = node;
  } else if (pos == end()) {
    tail_ = node;
  }

  ++size_;
  return ListIterator(this, node);
}

template <typename T>
list<T> list<T>::Divide() {
  list<T> second_part;
  if (size_ > 1) {
    Node* fast = head_;
    Node* slow = head_;

    size_type new_size = 1;

    while (fast->next != nullptr && fast->next->next != nullptr) {
      fast = fast->next->next;
      slow = slow->next;
      ++new_size;
    }
    second_part.tail_ = tail_;
    tail_ = slow;
    second_part.head_ = slow->next;

    second_part.head_->prev = nullptr;
    slow->next = nullptr;

    second_part.size_ = size_ - new_size;
    size_ = new_size;
  }
  return second_part;
}

template <typename T>
class list<T>::ListIterator {
  friend class list<T>;

 public:
  ListIterator() noexcept = default;
  ListIterator(const ListIterator& li) noexcept;

  reference operator*();

  ListIterator& operator++();
  ListIterator operator++(int);

  ListIterator& operator--();
  ListIterator operator--(int);

  ListIterator& operator=(const ListIterator& li) noexcept = default;
  bool operator==(const ListIterator& li) const noexcept;
  bool operator!=(const ListIterator& li) const noexcept;

 private:
  ListIterator(const list<T>* l, Node* cur) noexcept;

  void InsertBefore(Node* node);

  Node* current_;
  const list<T>* list_;
};

template <typename T>
list<T>::ListIterator::ListIterator(const ListIterator& li) noexcept
    : current_(li.current_), list_(li.list_) {}

template <typename T>
list<T>::ListIterator::ListIterator(const list<T>* l, Node* cur) noexcept
    : current_(cur), list_(l) {}

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() {
  return current_->data;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
  current_ = current_->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  ListIterator temp(*this);
  ++(*this);
  return temp;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
  if (current_ != nullptr) {
    current_ = current_->prev;
  } else {
    current_ = list_->tail_;
  }
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  ListIterator temp(*this);
  --(*this);
  return temp;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator& li) const noexcept {
  return current_ == li.current_ &&
         (current_ != nullptr || list_->tail_ == li.list_->tail_);
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator& li) const noexcept {
  return current_ != li.current_ ||
         (current_ == nullptr && list_->tail_ != li.list_->tail_);
}

template <typename T>
void list<T>::ListIterator::InsertBefore(Node* node) {
  if (current_ != nullptr) {
    node->InsertBetween(current_->prev, current_);
  } else {
    node->InsertBetween(list_->tail_, current_);
  }
}

template <typename T>
class list<T>::ListConstIterator : public list<T>::ListIterator {
  friend class list<T>;

 public:
  ListConstIterator() noexcept = default;
  ListConstIterator(const ListIterator& li) noexcept;
  using list<T>::ListIterator::ListIterator;
  const_reference operator*();

 private:
  using list<T>::ListIterator::operator*;
};

template <typename T>
list<T>::ListConstIterator::ListConstIterator(
    const list<T>::ListIterator& li) noexcept
    : list<T>::ListIterator(li) {}

template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*() {
  return ListIterator::operator*();
}

template <typename T>
class list<T>::Node {
 public:
  value_type data;
  Node* prev;
  Node* next;

  Node() noexcept;
  Node(value_type data) noexcept;
  Node(Node* prev, Node* next, value_type data) noexcept;

  void InsertBetween(Node* prev, Node* next) noexcept;
};

template <typename T>
list<T>::Node::Node() noexcept : next(nullptr), prev(nullptr) {}

template <typename T>
list<T>::Node::Node(value_type data) noexcept
    : data(data), prev(nullptr), next(nullptr) {}

template <typename T>
list<T>::Node::Node(Node* prev, Node* next, value_type data) noexcept
    : data(data), prev(prev), next(next) {
  InsertBetween(prev, next);
}

template <typename T>
void list<T>::Node::InsertBetween(Node* prev, Node* next) noexcept {
  this->prev = prev;
  this->next = next;
  if (prev != nullptr) {
    prev->next = this;
  }
  if (next != nullptr) {
    next->prev = this;
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_LIST_H_

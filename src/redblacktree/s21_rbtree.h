#ifndef S21_CONTAINERS_SRC_RBTREE_S21_RBTREE_H_
#define S21_CONTAINERS_SRC_RBTREE_S21_RBTREE_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {

enum class Color { kRed, kBlack };

template <typename Key, typename T, bool unique_values = false>
class RBTree {
 public:
  class Node;
  template <typename ret_value>
  class RBTreeTempIterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = RBTreeTempIterator<reference>;
  using const_iterator = RBTreeTempIterator<const_reference>;
  using size_type = size_t;

  // Constructors, operator= and Destructor
  RBTree();
  RBTree(std::initializer_list<value_type> const& items);
  RBTree(const RBTree& other);
  RBTree& operator=(const RBTree& other);
  RBTree(RBTree&& other) noexcept;
  RBTree& operator=(RBTree&& other) noexcept;
  ~RBTree();

  // Iterators
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Contains information
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Changing tree
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  iterator find(key_type key) noexcept;
  bool contains(key_type key) noexcept;
  iterator lower_bound(const Key& key) noexcept;
  iterator upper_bound(const Key& key) noexcept;
  void merge(RBTree& other) noexcept;
  void clear() noexcept;
  void swap(RBTree& other) noexcept;

  // Functions for testing
#ifdef RBTREE_TESTING
  bool CheckBlackHeight() const noexcept;
  size_t NodeBlackHeight(Node* node) const noexcept;
#endif
  

 private:
  Node* sentinel_ = nullptr;
  Node* root_ = nullptr;
  size_type size_ = 0;

  void InitSentinel() noexcept;
  void DestroyTree(Node* node) noexcept;
  void CopyTree(const RBTree& other);
  Node* CopyNodes(Node* src_node, Node* parent);
  void RotateLeft(Node* node) noexcept;
  void RotateRight(Node* node) noexcept;
  std::pair<Node*, bool> InsertNodeDirectly(Node* root, Node* new_node) noexcept;
  void mergeTreeUnique(RBTree& other) noexcept;
  Node* ExtractNode(iterator pos);
  void BalanceAfterInsert(Node* node) noexcept;
  void BalanceAfterRemove(Node* node) noexcept;
  Node* SearchMin(Node* node) noexcept;
  Node* SearchMax(Node* node) noexcept;
  void SetMinMax(Node* node) noexcept;
  void SwapNodesValues(Node* n1, Node* n2) noexcept;
};

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>::RBTree() : sentinel_(new Node) {}

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>::RBTree(std::initializer_list<value_type> const& items)
    : sentinel_(new Node) {
  for (auto item : items) {
    insert(item);
  }
}

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>::RBTree(const RBTree& other) : sentinel_(new Node) {
  if (other.root_ != nullptr) {
    CopyTree(other);
  }
}

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>& RBTree<Key, T, unique_values>::operator=(const RBTree& other) {
  if (this == &other) {
    return *this;
  }
  if (other.root_ != nullptr) {
    CopyTree(other);
  } else {
    clear();
  }
  return *this;
}

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>::RBTree(RBTree&& other) noexcept {
  swap(other);
}

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>& RBTree<Key, T, unique_values>::operator=(RBTree&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  clear();
  swap(other);
  return *this;
}

template <typename Key, typename T, bool unique_values>
RBTree<Key, T, unique_values>::~RBTree() {
  clear();
  delete sentinel_;
}

// Iterators

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::iterator RBTree<Key, T, unique_values>::begin() noexcept {
  return iterator(sentinel_->left);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::iterator RBTree<Key, T, unique_values>::end() noexcept {
  return iterator(sentinel_);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::const_iterator RBTree<Key, T, unique_values>::begin() const noexcept {
  return iterator(sentinel_->left);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::const_iterator RBTree<Key, T, unique_values>::end() const noexcept {
  return iterator(sentinel_);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::const_iterator RBTree<Key, T, unique_values>::cbegin()
    const noexcept {
  return const_iterator(sentinel_->left);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::const_iterator RBTree<Key, T, unique_values>::cend() const noexcept {
  return const_iterator(sentinel_);
}

// Contains information

template <typename Key, typename T, bool unique_values>
bool RBTree<Key, T, unique_values>::empty() const noexcept {
  return root_ == nullptr;
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::size_type RBTree<Key, T, unique_values>::size() const noexcept {
  return size_;
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::size_type RBTree<Key, T, unique_values>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

// Changing tree

template <typename Key, typename T, bool unique_values>
std::pair<typename RBTree<Key, T, unique_values>::iterator, bool>
RBTree<Key, T, unique_values>::insert(const value_type& value) {
  Node* new_node = new Node(value);
  auto result = InsertNodeDirectly(root_, new_node);
  if (result.second) {
    SetMinMax(result.first);
    ++size_;
    BalanceAfterInsert(result.first);
  } else {
    delete new_node;
  }
  return std::make_pair(iterator(result.first), result.second);
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::erase(iterator pos) {
  Node* delete_node = ExtractNode(pos);
  if (delete_node == root_) {
    clear();
    return;
  }
  delete delete_node;
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::iterator RBTree<Key, T, unique_values>::find(Key key) noexcept {
  Node* current = root_;
  while (current) {
    if (key == current->data.first) {
      return iterator(current);
    } else if (key < current->data.first) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return end();
}

template <typename Key, typename T, bool unique_values>
bool RBTree<Key, T, unique_values>::contains(Key key) noexcept {
  return find(key) != end();
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::iterator RBTree<Key, T, unique_values>::lower_bound(
    const Key& key) noexcept {
  Node* search = root_;
  Node* result = nullptr;

  while (search != nullptr) {
    if (search->data.first >= key) {
      result = search;
      search = search->left;
    } else {
      search = search->right;
    }
  }
  return (result == nullptr ? end() : iterator(result));
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::iterator RBTree<Key, T, unique_values>::upper_bound(
    const Key& key) noexcept {
  Node* search = root_;
  Node* result = nullptr;

  while (search != nullptr) {
    if (search->data.first > key) {
      result = search;
      search = search->left;
    } else {
      search = search->right;
    }
  }
  return (result == nullptr ? end() : iterator(result));
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::merge(RBTree& other) noexcept {
  if constexpr (unique_values) {
    mergeTreeUnique(other);
    return;
  }

  if (this == &other) {
    return;
  }
  iterator iter = other.begin();
  while (other.size_ != 0) {
    Node* move_node = iter.current_;
    ++iter;
    if (move_node->left != nullptr) {
      move_node->left->parent = move_node->parent;
    }
    if (move_node->right != nullptr) {
      move_node->right->parent = move_node->parent;
    }
    if (move_node->parent->left == move_node) {
      move_node->parent->left = nullptr;
    }
    if (move_node->parent->right == move_node) {
      move_node->parent->right = nullptr;
    }
    move_node->ClearPointers();
    --other.size_;
    auto result = InsertNodeDirectly(root_, move_node);
    SetMinMax(result.first);
    ++size_;
    BalanceAfterInsert(result.first);
  }
  other.InitSentinel();
  other.root_ = nullptr;

}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::mergeTreeUnique(RBTree& other) noexcept {
  if (this == &other) {
    return;
  }
  iterator iter = other.begin();
  while (iter != other.end()) {
    iterator possible = find((*iter).first);
    if (possible == end()) {
      iterator move_iter = iter;
      ++iter;
      Node* move_node = other.ExtractNode(move_iter);
      if (move_node == other.root_) {
        other.InitSentinel();
        other.size_ = 0;
        other.root_ = nullptr;
      }
      auto result = InsertNodeDirectly(root_, move_node);
      SetMinMax(result.first);
      ++size_;
      BalanceAfterInsert(result.first);
    } else {
      ++iter;
    }
  }
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::clear() noexcept {
  DestroyTree(root_);
  if (sentinel_ != nullptr) {
    InitSentinel();
  }
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::swap(RBTree& other) noexcept {
  std::swap(sentinel_, other.sentinel_);
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
}

#ifdef RBTREE_TESTING
template <typename Key, typename T, bool unique_values>
bool RBTree<Key, T, unique_values>::CheckBlackHeight() const noexcept {
  if (root_ == nullptr) {
    return true;
  }
  Node* check_node = sentinel_->left;
  while (check_node->left != nullptr || check_node->right != nullptr) {
    check_node = check_node->NextNode();
  }
  size_t height = NodeBlackHeight(check_node);
  check_node = check_node->NextNode();
  while (check_node != sentinel_) {
    if (check_node->left == nullptr && check_node->right == nullptr) {
      size_t current_height = NodeBlackHeight(check_node);
      if (height != current_height) {
        return false;
      }
    }
    check_node = check_node->NextNode();
  }
  return true;
}

template <typename Key, typename T, bool unique_values>
size_t RBTree<Key, T, unique_values>::NodeBlackHeight(Node* node) const noexcept {
  size_t result = 0;
  while (node != nullptr && node != root_) {
    if (node->color == Color::kBlack) {
      ++result;
    }
    node = node->parent;
  }
  return result;
}
#endif

// private functions

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::InitSentinel() noexcept {
  sentinel_->parent = nullptr;
  sentinel_->left = sentinel_;
  sentinel_->right = sentinel_;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::DestroyTree(Node* node) noexcept {
  if (node == nullptr) {
    return;
  }
  DestroyTree(node->left);
  DestroyTree(node->right);
  delete node;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::CopyTree(const RBTree& other) {
  Node* tmp = CopyNodes(other.root_, nullptr);
  clear();
  root_ = tmp;
  size_ = other.size_;
  root_->parent = sentinel_;
  sentinel_->parent = root_;
  sentinel_->left = SearchMin(root_);
  sentinel_->right = SearchMax(root_);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::Node* RBTree<Key, T, unique_values>::CopyNodes(Node* src_node,
                                                         Node* parent) {
  if (!src_node) {
    return nullptr;
  }
  Node* new_node = new Node(src_node->data);
  new_node->parent = parent;
  new_node->color = src_node->color;
  new_node->left = CopyNodes(src_node->left, new_node);
  new_node->right = CopyNodes(src_node->right, new_node);

  return new_node;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::RotateLeft(Node* node) noexcept {
  if (node == nullptr || node->right == nullptr) {
    return;
  }
  // Выбираем опорным узлом правого потомка
  Node* pivot = node->right;
  // Отдаем левого потомка опорного узла нашему узлу node
  node->right = pivot->left;
  // Если потомок есть, он должен признать усыновление(удочерение)
  if (pivot->left != nullptr) {
    pivot->left->parent = node;
  }
  // Опорный узел усыновляется предыдущим родителем узла node
  pivot->parent = node->parent;
  // Если переданный узел был корнем, опорный становится новым корнем
  if (node == root_) {
    root_ = pivot;
    sentinel_->parent = root_;
  } else if (node == node->parent->left) {
    // Опорный элемент становится потомком с нужной стороны от бывшего родителя
    // node
    node->parent->left = pivot;
  } else {
    node->parent->right = pivot;
  }
  // Опорный узел и node меняюся ролями в этой Санта-Барбаре - родитель стал
  // левым потомком, бывший потомок (опорный узел) стал родителем
  pivot->left = node;
  node->parent = pivot;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::RotateRight(Node* node) noexcept {
  //  Поворот вправо осуществляется аналогично, симметрично левому
  if (node == nullptr || node->left == nullptr) {
    return;
  }
  Node* pivot = node->left;
  node->left = pivot->right;
  if (pivot->right != nullptr) {
    pivot->right->parent = node;
  }
  pivot->parent = node->parent;
  if (node == root_) {
    root_ = pivot;
    sentinel_->parent = root_;
  } else if (node == node->parent->left) {
    node->parent->left = pivot;
  } else {
    node->parent->right = pivot;
  }
  pivot->right = node;
  node->parent = pivot;
}

template <typename Key, typename T, bool unique_values>
std::pair<typename RBTree<Key, T, unique_values>::Node*, bool>
RBTree<Key, T, unique_values>::InsertNodeDirectly(Node* root, Node* new_node) noexcept {
  Node* current = root;
  Node* parent = nullptr;

  while (current) {
    parent = current;
    if (new_node->data.first < current->data.first) {
      current = current->left;
    } else if (!unique_values || new_node->data.first > current->data.first) {
      current = current->right;
    } else {
      return std::make_pair(current, false);
    }
  }
  if (parent == nullptr) {
    root_ = new_node;
  } else {
    if (new_node->data.first < parent->data.first) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
    new_node->parent = parent;
  }
  return std::make_pair(new_node, true);
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::Node* RBTree<Key, T, unique_values>::ExtractNode(iterator pos) {
  if (pos == end()) {
    return nullptr;
  }
  Node* delete_node = pos.current_;
  // Для начала обрабатываем случаи К2 и Ч2 для удаления узла с двумя потомками,
  // которые сводятся к удалению узла с одним или нулем потомков путем свапа
  // элемента с ближайшим слева (самый правый в левом поддереве) или справа
  // (самый левый в правом поддереве)
  if (delete_node->left != nullptr && delete_node->right != nullptr) {
    // Будем искать ближайший слева (самый правый в левом поддереве)
    Node* replace_node = SearchMax(delete_node->left);
    SwapNodesValues(delete_node, replace_node);
  }
  // Далее случай удаления черного узла с одним ребенком Ч1 (К1 из за свойств
  // КЧД не может существовать, иначе нарушится черная выстота). Этот ребенок
  // будет красный - просто меняем значения этих двух узлов (в моей реализации
  // наоборот по сути меняем все кроме значений и удаляем узел - чтобы не
  // инвалидировались итераторы дерева должен удаляться указатель именно на
  // нужный узел
  if (delete_node->color == Color::kBlack &&
      ((delete_node->left == nullptr) != (delete_node->right == nullptr))) {
    Node* replace_node;
    if (delete_node->left != nullptr) {
      replace_node = delete_node->left;
    } else {
      replace_node = delete_node->right;
    }
    SwapNodesValues(delete_node, replace_node);
  }
  // Обработка Ч0 - нарушает черную высоту дерева и требует балансировки
  if (delete_node->color == Color::kBlack && delete_node->left == nullptr &&
      delete_node->right == nullptr) {
    BalanceAfterRemove(delete_node);
  }
  if (delete_node == root_) {
    return delete_node;
  } else {
    if (delete_node == delete_node->parent->left) {
      delete_node->parent->left = nullptr;
    } else {
      delete_node->parent->right = nullptr;
    }
    if (delete_node == sentinel_->left) {
      sentinel_->left = SearchMin(root_);
    }
    if (delete_node == sentinel_->right) {
      sentinel_->right = SearchMax(root_);
    }
  }
  --size_;
  delete_node->ClearPointers();
  return delete_node;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::BalanceAfterInsert(Node* node) noexcept {
  // Проверям, если у вставленного элемента нет родителя, то это корень -
  // соответственно красим его в черный и выходим из функции
  if (node->parent == nullptr) {
    node->color = Color::kBlack;
    root_ = node;
    root_->parent = sentinel_;
    sentinel_->parent = root_;
    sentinel_->left = root_;
    sentinel_->right = root_;
    return;
  }
  while (node != root_ && node->parent->color == Color::kRed) {
    Node* parent = node->parent;
    Node* grandparent = parent->parent;
    Node* pibling =
        (parent == grandparent->left) ? grandparent->right : grandparent->left;
    if (pibling != nullptr && pibling->color == Color::kRed) {
      // Случай 1 - родитель и дядя/тетя красные. Здесь мы просто выполняем
      // перекрашивание их в черный, прародителя в красный и продолжаем
      // проверку уже для прародителя
      parent->color = Color::kBlack;
      pibling->color = Color::kBlack;
      grandparent->color = Color::kRed;
      node = grandparent;
    } else {
      // Случай 2 - дядя/тетя черные. Предварительно рассматриваем более сложные
      // случаи, в которых потребудется 2 поворота - малый относительно
      // родителя и затем уже  большой относительно прародителя. Их можно
      // описать как Left-Right Case и Right-Left Case
      if (node == parent->right && parent == grandparent->left) {
        // Левый поворот относительно родителя
        RotateLeft(parent);
        std::swap(node, parent);
      } else if (node == parent->left && parent == grandparent->right) {
        // Правый поворот относительно родителя
        RotateRight(parent);
        std::swap(node, parent);
      }
      // После приведения (если потребовалось) к Right-Right Case или Left-Left
      // Case, выполняем большой поворот относительно прародителя
      if (node == parent->left) {
        RotateRight(grandparent);
      } else {
        RotateLeft(grandparent);
      }
      parent->color = Color::kBlack;
      grandparent->color = Color::kRed;
    }
  }
  root_->color = Color::kBlack;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::BalanceAfterRemove(Node* node) noexcept {
  Node* parent = node->parent;
  while (node != root_ && (node == nullptr || node->color == Color::kBlack)) {
    if (node == parent->left) {
      Node* sibling = parent->right;
      if (sibling->color == Color::kRed) {
        // Случай 1: У кузина (sibling) красный цвет - мы можем выполнить
        // поворот и перекраску
        parent->color = Color::kRed;
        sibling->color = Color::kBlack;
        RotateLeft(parent);
        sibling = parent->right;
      }

      if (sibling->color == Color::kBlack &&
          (sibling->left == nullptr || sibling->left->color == Color::kBlack) &&
          (sibling->right == nullptr ||
           sibling->right->color == Color::kBlack)) {
        // Случай 2: Кузин (sibling) черные, и у кузина нет красных потомков
        // Мы можем перекрасить кузина в красный и передать проблему вверх к
        // родителю. Если цвет родителя красный - то перекрашиваем его в черный
        // и завершаем балансировку
        sibling->color = Color::kRed;
        if (parent->color == Color::kRed) {
          parent->color = Color::kBlack;
          break;
        }
        node = parent;
        parent = node->parent;
      } else {
        // Случай 3: Кузин(а) (sibling) черные, и у кузины есть хотя бы один
        // красный потомок Мы можем выполнить поворот и перекраску, чтобы
        // преобразовать ситуацию в Случай 4
        if (sibling->left != nullptr && sibling->left->color == Color::kRed &&
            (sibling->right == nullptr ||
             sibling->right->color == Color::kBlack)) {
          // Правый потомок кузины черный (или отсутствует)
          // Мы выполняем правый поворот на кузине
          sibling->color = Color::kRed;
          sibling->left->color = Color::kBlack;
          RotateRight(sibling);
          sibling = parent->right;
        }

        // Случай 4: Кузина (sibling) черные, и у кузины есть хотя бы один
        // красный потомок Мы выполняем поворот и перекраску, чтобы восстановить
        // свойства дерева
        sibling->color = parent->color;
        parent->color = Color::kBlack;
        sibling->right->color = Color::kBlack;
        RotateLeft(parent);
        break;
      }
    } else {
      // Аналогичные случаи для правого узла и кузины
      Node* sibling = parent->left;
      if (sibling->color == Color::kRed) {
        parent->color = Color::kRed;
        sibling->color = Color::kBlack;
        RotateRight(parent);
        sibling = parent->left;
      }

      if (sibling->color == Color::kBlack &&
          (sibling->left == nullptr || sibling->left->color == Color::kBlack) &&
          (sibling->right == nullptr ||
           sibling->right->color == Color::kBlack)) {
        sibling->color = Color::kRed;
        if (parent->color == Color::kRed) {
          parent->color = Color::kBlack;
          break;
        }
        node = parent;
        parent = node->parent;
      } else {
        if (sibling->right != nullptr && sibling->right->color == Color::kRed &&
            (sibling->left == nullptr ||
             sibling->left->color == Color::kBlack)) {
          sibling->color = Color::kRed;
          sibling->right->color = Color::kBlack;
          RotateLeft(sibling);
          sibling = parent->left;
        }

        sibling->color = parent->color;
        parent->color = Color::kBlack;
        sibling->left->color = Color::kBlack;
        RotateRight(parent);
        break;
      }
    }
  }
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::Node* RBTree<Key, T, unique_values>::SearchMin(Node* node) noexcept {
  while (node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::Node* RBTree<Key, T, unique_values>::SearchMax(Node* node) noexcept {
  while (node->right) {
    node = node->right;
  }
  return node;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::SetMinMax(Node* node) noexcept {
  if (node->data.first < sentinel_->left->data.first) {
    sentinel_->left = node;
  }
  if (node->data.first >= sentinel_->right->data.first) {
    sentinel_->right = node;
  }
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::SwapNodesValues(Node* n1, Node* n2) noexcept {
  if (n2->parent->left == n2) {
    n2->parent->left = n1;
  } else {
    n2->parent->right = n1;
  }
  if (n1 == root_) {
    root_ = n2;
    sentinel_->parent = root_;
  } else {
    if (n1->parent->left == n1) {
      n1->parent->left = n2;
    } else {
      n1->parent->right = n2;
    }
  }
  std::swap(n1->parent, n2->parent);
  std::swap(n1->left, n2->left);
  std::swap(n1->right, n2->right);
  std::swap(n1->color, n2->color);
  if (n1->left) {
    n1->left->parent = n1;
  }
  if (n1->right) {
    n1->right->parent = n1;
  }
  if (n2->left) {
    n2->left->parent = n2;
  }
  if (n2->right) {
    n2->right->parent = n2;
  }
}

template <typename Key, typename T, bool unique_values>
class RBTree<Key, T, unique_values>::Node {
 public:
  value_type data;
  Node* parent = nullptr;
  Node* left;
  Node* right;
  Color color = Color::kRed;

  Node() : left(this), right(this) {}
  explicit Node(value_type value)
      : data(value), left(nullptr), right(nullptr) {}

  Node* NextNode() const noexcept;
  Node* PrevNode() const noexcept;
  void ClearPointers() noexcept;
};

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::Node* RBTree<Key, T, unique_values>::Node::NextNode() const noexcept {
  Node* node = const_cast<Node*>(this);
  if (node->color == Color::kRed &&
      (node->parent == nullptr || node->parent->parent == node)) {
    node = node->left;
  } else if (node->right != nullptr) {
    node = node->right;
    while (node->left != nullptr) {
      node = node->left;
    }
  } else {
    Node* parent = node->parent;
    while (node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    if (node->right != parent) {
      node = parent;
    }
  }
  return node;
}

template <typename Key, typename T, bool unique_values>
typename RBTree<Key, T, unique_values>::Node* RBTree<Key, T, unique_values>::Node::PrevNode() const noexcept {
  Node* node = const_cast<Node*>(this);
  if (node->color == Color::kRed &&
      (node->parent == nullptr || node->parent->parent == node)) {
    node = node->right;
  } else if (node->left != nullptr) {
    node = node->left;
    while (node->right != nullptr) {
      node = node->right;
    }
  } else {
    Node* parent = node->parent;
    while (node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    if (node->left != parent) {
      node = parent;
    }
  }
  return node;
}

template <typename Key, typename T, bool unique_values>
void RBTree<Key, T, unique_values>::Node::ClearPointers() noexcept {
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  color = Color::kRed;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
class RBTree<Key, T, unique_values>::RBTreeTempIterator {
 public:
  template <typename>
  friend class RBTreeTempIterator;
  friend class RBTree<Key, T, unique_values>;

  RBTreeTempIterator() = default;
  explicit RBTreeTempIterator(Node* node) : current_(node){};
  RBTreeTempIterator& operator=(const RBTreeTempIterator& other) noexcept =
      default;
  template <typename U>
  RBTreeTempIterator(const RBTreeTempIterator<U>& it)
      : current_{it.current_} {};

  ret_value operator*() const;
  RBTreeTempIterator& operator++();
  RBTreeTempIterator operator++(int);
  RBTreeTempIterator& operator--();
  RBTreeTempIterator operator--(int);
  bool operator==(const RBTreeTempIterator& other) const noexcept;
  bool operator!=(const RBTreeTempIterator& other) const noexcept;

 protected:
  Node* current_;
};

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
ret_value RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator*() const {
  return current_->data;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>&
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator++() {
  current_ = current_->NextNode();
  return *this;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator++(int) {
  iterator tmp(current_);
  ++(*this);
  return tmp;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>&
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator--() {
  current_ = current_->PrevNode();
  return *this;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>
RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator--(int) {
  iterator tmp({current_});
  --(*this);
  return tmp;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
bool RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator==(
    const RBTreeTempIterator& other) const noexcept {
  return current_ == other.current_;
}

template <typename Key, typename T, bool unique_values>
template <typename ret_value>
bool RBTree<Key, T, unique_values>::RBTreeTempIterator<ret_value>::operator!=(
    const RBTreeTempIterator& other) const noexcept {
  return current_ != other.current_;
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_RBTREE_S21_RBTREE_H_

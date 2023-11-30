#define RBTREE_TESTING

#include "redblacktree/s21_rbtree.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>
#include <utility>

TEST(TestTree, BasicConstructor) {
  s21::RBTree<unsigned, int32_t> tr;
  EXPECT_EQ(0, tr.size());
}

TEST(TestTree, InitializerListConstructor) {
  s21::RBTree<uint64_t, char> tr(
      {{1, 'a'}, {2, 'b'}, {3, 'o'}, {4, 'b'}, {5, 'a'}});

  EXPECT_EQ(5, tr.size());
  EXPECT_EQ(1, (*tr.begin()).first);
  EXPECT_EQ('a', (*tr.begin()).second);
  auto iter = tr.end();
  --iter;
  EXPECT_EQ(5, (*iter).first);
  EXPECT_EQ('a', (*iter).second);
}

TEST(TestTree, CopyConstructor) {
  s21::RBTree<int64_t, int8_t> origin({{1, 5}, {2, 4}, {3, 3}, {4, 2}, {5, 1}});
  s21::RBTree<int64_t, int8_t> copy(origin);

  EXPECT_TRUE(origin.size() == copy.size());
  auto iter_origin = origin.begin();
  auto iter_copy = copy.begin();
  EXPECT_NE(iter_origin, iter_copy);
  for (; iter_origin != origin.end(); ++iter_origin, ++iter_copy) {
    EXPECT_EQ((*iter_origin).first, (*iter_copy).first);
    EXPECT_EQ((*iter_origin).second, (*iter_copy).second);
  }
}

TEST(TestTree, CopyAssignmentOperator) {
  s21::RBTree<size_t, bool> origin({{4, 0}, {8, 0}, {12, 0}, {16, 0}, {20, 0}});
  s21::RBTree<size_t, bool> copied;
  s21::RBTree<size_t, bool> empty;
  copied = origin;

  EXPECT_EQ(5, origin.size());
  EXPECT_EQ(5, copied.size());
  size_t foo = 4;
  for (auto iter = copied.begin(); iter != copied.end(); iter++) {
    EXPECT_EQ(foo, (*iter).first);
    EXPECT_EQ(false, (*iter).second);
    foo += 4;
  }

  copied = copied;
  EXPECT_EQ(5, copied.size());
  copied = empty;
  EXPECT_EQ(0, copied.size());
}

TEST(TestTree, MoveConstructor) {
  s21::RBTree<uint32_t, int16_t> origin(
      {{6, 5}, {5, 4}, {4, 3}, {3, 2}, {2, 1}});
  s21::RBTree<uint32_t, int16_t> moved(std::move(origin));

  EXPECT_EQ(0, origin.size());
  EXPECT_EQ(5, moved.size());
  int64_t abobich = 1;
  for (auto iter = moved.begin(); iter != moved.end(); ++iter, ++abobich) {
    EXPECT_EQ(abobich + 1, (*iter).first);
    EXPECT_EQ(abobich, (*iter).second);
  }
}

TEST(TestTree, MoveAssignmentOperator) {
  s21::RBTree<char, bool> origin({{'F', 0}, {'B', 1}, {'I', 0}});
  s21::RBTree<char, bool> moved;

  EXPECT_EQ(3, origin.size());
  EXPECT_EQ(0, moved.size());
  moved = std::move(origin);
  EXPECT_EQ(0, origin.size());
  EXPECT_EQ(3, moved.size());

  auto iter = moved.begin();
  EXPECT_EQ('B', (*iter).first);
  EXPECT_EQ(true, (*iter).second);
  ++iter;
  EXPECT_EQ('F', (*iter).first);
  EXPECT_EQ(false, (*iter).second);
  iter++;
  EXPECT_EQ('I', (*iter).first);
  EXPECT_EQ(false, (*iter).second);

  moved = std::move(moved);
}

TEST(TestTree, Iterator) {
  s21::RBTree<int, int> tree({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});

  auto iter_b = tree.begin();
  auto iter_e = tree.end();
  EXPECT_EQ(1, (*iter_b).first);
  ++iter_b;
  EXPECT_EQ(2, (*iter_b).first);
  iter_b++;
  EXPECT_EQ(3, (*iter_b).first);
  ++iter_b;
  EXPECT_EQ(4, (*iter_b).first);
  ++iter_b;
  EXPECT_EQ(5, (*iter_b).first);
  iter_b++;
  ++iter_b;
  EXPECT_EQ(1, (*iter_b).first);
  --iter_e;
  EXPECT_EQ(5, (*iter_e).first);
  iter_e--;
  EXPECT_EQ(4, (*iter_e).first);
  --iter_e;
  EXPECT_EQ(3, (*iter_e).first);
  iter_e--;
  EXPECT_EQ(2, (*iter_e).first);
  --iter_e;
  EXPECT_EQ(1, (*iter_e).first);
  iter_e--;
  --iter_e;
  EXPECT_EQ(5, (*iter_e).first);
}

TEST(TestTree, InsertBegin) {
  s21::RBTree<char, bool> tree({{'D', 0}, {'E', 1}, {'F', 0}});
  auto iter = tree.begin();
  EXPECT_EQ(true, tree.CheckBlackHeight());

  tree.insert({'C', 1});
  EXPECT_EQ(4, tree.size());
  EXPECT_EQ('D', (*iter).first);
  iter = tree.begin();
  EXPECT_EQ('C', (*iter).first);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  tree.insert({'B', 1});
  EXPECT_EQ(5, tree.size());
  EXPECT_EQ('C', (*iter).first);
  iter = tree.begin();
  EXPECT_EQ('B', (*iter).first);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  auto check = tree.insert({'A', 0});
  EXPECT_EQ(true, check.second);
  EXPECT_EQ(6, tree.size());
  EXPECT_EQ('B', (*iter).first);
  iter = tree.begin();
  EXPECT_EQ('A', (*iter).first);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  check = tree.insert({'A', 1});
  EXPECT_EQ(true, check.second);
  iter = tree.begin();
  EXPECT_EQ(7, tree.size());
  EXPECT_EQ('A', (*iter).first);
  EXPECT_EQ(0, (*iter).second);
  iter++;
  EXPECT_EQ('A', (*iter).first);
  EXPECT_EQ(1, (*iter).second);
  EXPECT_EQ(true, tree.CheckBlackHeight());
}

TEST(TestTree, InsertUniqueBegin) {
  s21::RBTree<char, bool, true> tree({{'D', 0}, {'E', 1}, {'F', 0}});
  auto iter = tree.begin();
  EXPECT_EQ(true, tree.CheckBlackHeight());

  tree.insert({'C', 1});
  EXPECT_EQ(4, tree.size());
  EXPECT_EQ('D', (*iter).first);
  iter = tree.begin();
  EXPECT_EQ('C', (*iter).first);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  tree.insert({'B', 1});
  EXPECT_EQ(5, tree.size());
  EXPECT_EQ('C', (*iter).first);
  iter = tree.begin();
  EXPECT_EQ('B', (*iter).first);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  tree.insert({'A', 0});
  EXPECT_EQ(6, tree.size());
  EXPECT_EQ('B', (*iter).first);
  iter = tree.begin();
  EXPECT_EQ('A', (*iter).first);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  tree.insert({'A', 1});
  EXPECT_EQ(6, tree.size());
  EXPECT_EQ('A', (*iter).first);
  EXPECT_EQ(0, (*iter).second);
  EXPECT_EQ(true, tree.CheckBlackHeight());

  auto check = tree.insert({'A', 1});
  EXPECT_EQ(false, check.second);
  EXPECT_EQ(6, tree.size());
  EXPECT_EQ('A', (*iter).first);
  EXPECT_EQ(0, (*iter).second);
  ++iter;
  EXPECT_EQ(true, tree.CheckBlackHeight());

  check = tree.insert({'B', 1});
  EXPECT_EQ(false, check.second);
  EXPECT_EQ(6, tree.size());
  EXPECT_EQ(true, tree.CheckBlackHeight());

  check = tree.insert({'B', 0});
  EXPECT_EQ(false, check.second);
  EXPECT_EQ(6, tree.size());
  EXPECT_EQ('B', (*iter).first);
  EXPECT_EQ(1, (*iter).second);
  EXPECT_EQ(true, tree.CheckBlackHeight());
}

TEST(TestTree, InsertMiddle) {
  s21::RBTree<size_t, int8_t> tree({{3, 3},
                                    {5, 5},
                                    {15, 15},
                                    {11, 11},
                                    {13, 13},
                                    {7, 7},
                                    {9, 9},
                                    {17, 17},
                                    {1, 1},
                                    {19, 19}});

  EXPECT_EQ(10, tree.size());
  EXPECT_EQ(true, tree.CheckBlackHeight());
  for (size_t i = 0; i < 10; ++i) {
    tree.insert({i * 2, i * 2});
    EXPECT_EQ(11 + i, tree.size());
    EXPECT_TRUE(tree.CheckBlackHeight());
  }

  size_t check_key = 0;
  for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
    EXPECT_EQ(check_key, (*iter).first);
    EXPECT_EQ(check_key, (*iter).second);
    ++check_key;
  }

  for (size_t i = 0; i < 20; ++i) {
    tree.insert({i, i});
    EXPECT_EQ(21 + i, tree.size());
    EXPECT_TRUE(tree.CheckBlackHeight());
  }

  auto iter = tree.end();
  check_key = 19;
  do {
    --iter;
    EXPECT_EQ(check_key, (*iter).first);
    EXPECT_EQ(check_key, (*iter).second);
    iter--;
    EXPECT_EQ(check_key, (*iter).first);
    EXPECT_EQ(check_key, (*iter).second);
    --check_key;
  } while (iter != tree.begin());
}

TEST(TestTree, InsertUniqueMiddle) {
  s21::RBTree<size_t, int8_t, true> tree({{3, 3},
                                    {5, 5},
                                    {15, 15},
                                    {11, 11},
                                    {13, 13},
                                    {7, 7},
                                    {9, 9},
                                    {17, 17},
                                    {1, 1},
                                    {19, 19}});

  EXPECT_EQ(10, tree.size());
  EXPECT_EQ(true, tree.CheckBlackHeight());
  for (size_t i = 0; i < 10; ++i) {
    tree.insert({i * 2, i * 2});
    EXPECT_EQ(11 + i, tree.size());
    EXPECT_TRUE(tree.CheckBlackHeight());
  }

  size_t check_key = 0;
  for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
    EXPECT_EQ(check_key, (*iter).first);
    EXPECT_EQ(check_key, (*iter).second);
    ++check_key;
  }

  for (size_t i = 0; i < 20; ++i) {
    tree.insert({i, i});
    EXPECT_EQ(20, tree.size());
    EXPECT_TRUE(tree.CheckBlackHeight());
  }

  auto iter = tree.end();
  check_key = 19;
  do {
    --iter;
    EXPECT_EQ(check_key, (*iter).first);
    EXPECT_EQ(check_key, (*iter).second);
    --check_key;
  } while (iter != tree.begin());
}

TEST(TestTree, InsertEnd) {
  s21::RBTree<int, int> tree({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});

  EXPECT_EQ(5, tree.size());
  EXPECT_TRUE(tree.CheckBlackHeight());

  for (int i = 6; i < 21; ++i) {
    tree.insert({i, 0});
    EXPECT_TRUE(tree.CheckBlackHeight());
    EXPECT_EQ(i, tree.size());
    auto iter = tree.end();
    --iter;
    EXPECT_EQ(i, (*iter).first);
  }

  for (int i = 1; i < 11; ++i) {
    tree.insert({20, i});
    EXPECT_TRUE(tree.CheckBlackHeight());
    EXPECT_EQ(20 + i, tree.size());
  }

  auto iter = tree.end();
  --iter;
  for (int i = 10; i > 0; --i) {
    EXPECT_EQ(i, (*iter).second);
    EXPECT_EQ(20, (*iter).first);
    --iter;
  }
}

TEST(TestTree, InsertUniqueEnd) {
  s21::RBTree<int, int, true> tree({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});

  EXPECT_EQ(5, tree.size());
  EXPECT_TRUE(tree.CheckBlackHeight());

  for (int i = 6; i < 21; ++i) {
    tree.insert({i, 0});
    EXPECT_TRUE(tree.CheckBlackHeight());
    EXPECT_EQ(i, tree.size());
    auto iter = tree.end();
    --iter;
    EXPECT_EQ(i, (*iter).first);
  }

  for (int i = 1; i < 11; ++i) {
    tree.insert({20, i});
    EXPECT_TRUE(tree.CheckBlackHeight());
    EXPECT_EQ(20, tree.size());
  }

  auto iter = tree.end();
  --iter;
  for (int i = 20; i > 0; --i) {
    EXPECT_EQ(0, (*iter).second);
    EXPECT_EQ(i, (*iter).first);
    --iter;
  }
}

TEST(TestTree, EmptySizeMaxSize) {
  s21::RBTree<size_t, bool> abobus;

  EXPECT_TRUE(abobus.empty());
  EXPECT_EQ(0, abobus.size());
  EXPECT_TRUE(abobus.max_size() > 1e+12);
}

TEST(TestTree, EraseSimple) {
  s21::RBTree<double, double, true> abobik;

  for (size_t i = 0; i < 1026; ++i) {
    abobik.insert({i, i + 3.14});
    EXPECT_EQ(i + 1, abobik.size());
    EXPECT_TRUE(abobik.CheckBlackHeight());
  }

  size_t size = 1026;
  for (size_t i = 100; i < 926; ++i) {
    auto iter = abobik.find(i);
    abobik.erase(iter);
    EXPECT_TRUE(abobik.CheckBlackHeight());
    EXPECT_EQ(--size, abobik.size());
  }

  for (size_t i = 0; i < 100; ++i) {
    auto iter = abobik.begin();
    abobik.erase(iter);
    EXPECT_TRUE(abobik.CheckBlackHeight());
    EXPECT_EQ(--size, abobik.size());
  }

  while (abobik.size() > 1) {
    auto iter = abobik.end();
    --iter;
    abobik.erase(iter);
    EXPECT_TRUE(abobik.CheckBlackHeight());
    EXPECT_EQ(--size, abobik.size());
  }
  auto iter = abobik.end();
  --iter;
  abobik.erase(iter);
  EXPECT_TRUE(abobik.CheckBlackHeight());
  EXPECT_EQ(--size, abobik.size());
}

TEST(TestTree, EraseBigRandom1) {
  s21::RBTree<int, int, true> vzhuh;

  for (size_t i = 0; i < 1000000; ++i) {
    int r = rand() % 200000;
    vzhuh.insert({r, i});
  }
  EXPECT_TRUE(vzhuh.CheckBlackHeight());
  for (size_t i = 0; i < 1000000; ++i) {
    int f = rand() % 200000;
    auto iter = vzhuh.find(f);
    if (iter != vzhuh.end()) {
      vzhuh.erase(iter);
    }
    if (i % 10000 == 0) {
      EXPECT_TRUE(vzhuh.CheckBlackHeight());
    }
  }
}

TEST(TestTree, EraseBigRandom2) {
  s21::RBTree<int, int, true> vzhuh;

  for (size_t i = 0; i < 1000000; ++i) {
    int r = rand() % 100000;
    vzhuh.insert({r, i});
  }
  EXPECT_TRUE(vzhuh.CheckBlackHeight());
  for (size_t i = 0; i < 2000000; ++i) {
    int f = rand() % 100000;
    auto iter = vzhuh.find(f);
    if (iter != vzhuh.end()) {
      vzhuh.erase(iter);
    }
    if (i % 10000 == 0) {
      EXPECT_TRUE(vzhuh.CheckBlackHeight());
    }
  }
}

TEST(TestTree, EraseBigRandom3) {
  s21::RBTree<int, int, true> vzhuh;

  for (size_t i = 0; i < 500000; ++i) {
    int r = rand() % 50000;
    vzhuh.insert({r, i});
  }
  EXPECT_TRUE(vzhuh.CheckBlackHeight());
  for (size_t i = 0; i < 1000000; ++i) {
    int f = rand() % 50000;
    auto iter = vzhuh.find(f);
    if (iter != vzhuh.end()) {
      vzhuh.erase(iter);
    }
    if (i % 10000 == 0) {
      EXPECT_TRUE(vzhuh.CheckBlackHeight());
    }
  }
}

TEST(TestTree, EraseAndPaste) {
  s21::RBTree<int, int, true> derevo;

  for (size_t i = 0; i < 1000; ++i) {
    derevo.insert({i, i});
  }
  for (size_t i = 0; i < 1000; ++i) {
    auto iter = derevo.find(i);
    derevo.erase(iter);
    EXPECT_TRUE(derevo.CheckBlackHeight());
    derevo.insert({i, i});
    EXPECT_EQ(1000, derevo.size());
  }
}

TEST(TestTree, MergeSimple) {
  s21::RBTree<int, int> dest({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});
  s21::RBTree<int, int> src({{6, 0}, {8, 0}, {7, 0}, {9, 0}, {10, 0}});

  dest.merge(src);
  EXPECT_EQ(10, dest.size());
  EXPECT_EQ(0, src.size());
}

TEST(TestTree, MergeSimpleDuplicates) {
  s21::RBTree<int, int> dest({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});
  s21::RBTree<int, int> src({{5, 0}, {4, 0}, {3, 0}, {2, 0}});

  dest.merge(src);
  EXPECT_EQ(9, dest.size());
  EXPECT_EQ(0, src.size());
}

TEST(TestTree, MergeUniqueSimple) {
  s21::RBTree<int, int, true> dest({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});
  s21::RBTree<int, int, true> src({{6, 0}, {8, 0}, {7, 0}, {9, 0}, {10, 0}});

  dest.merge(src);
  EXPECT_EQ(10, dest.size());
  EXPECT_EQ(0, src.size());
}

TEST(TestTree, MergeUniqueDuplicates) {
  s21::RBTree<int, int, true> dest({{1, 0}, {2, 0}, {5, 0}, {4, 0}, {3, 0}});
  s21::RBTree<int, int, true> src({{6, 0}, {8, 0}, {1, 0}, {2, 0}, {3, 0}});

  dest.merge(src);
  EXPECT_EQ(7, dest.size());
  EXPECT_EQ(3, src.size());
}

TEST(TestTree, LowerBound) {
  s21::RBTree<int, int> birch({{1, 0}, {2, 0}, {2, 0}, {2, 0}, {3, 0}});

  auto iter = birch.lower_bound(2);
  EXPECT_EQ(2, (*iter).first);
  --iter;
  EXPECT_EQ(1, (*iter).first);
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  EXPECT_EQ(3, (*iter).first);
}

TEST(TestTree, UpperBound) {
  s21::RBTree<int, int> birch({{1, 0}, {2, 0}, {2, 0}, {2, 0}, {3, 0}});

  auto iter = birch.upper_bound(2);
  EXPECT_EQ(3, (*iter).first);
  --iter;
  EXPECT_EQ(2, (*iter).first);
  --iter;
  EXPECT_EQ(2, (*iter).first);
  iter = birch.upper_bound(1);
  EXPECT_EQ(2, (*iter).first);
  --iter;
  EXPECT_EQ(1, (*iter).first);
}

// for (auto iter = dest.begin(); iter != dest.end(); ++iter) {
//   std::cout << (*iter).first << std::endl;
// }
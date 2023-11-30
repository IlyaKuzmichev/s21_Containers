#include <gtest/gtest.h>

#include <iostream>

#include "s21_containersplus.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> test;
  EXPECT_TRUE(test.empty());
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> original = {1, 2, 2, 3, 3, 3};
  s21::multiset<int> copy(original);
  EXPECT_EQ(original.size(), 6);
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(2));
  EXPECT_TRUE(copy.contains(3));
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> original = {1, 2, 3, 1};

  s21::multiset<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 4);

  EXPECT_TRUE(moved.contains(1));
  EXPECT_TRUE(moved.contains(2));
  EXPECT_TRUE(moved.contains(3));
}

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::multiset<int> source;
  source.insert(1);
  source.insert(2);
  source.insert(2);

  s21::multiset<int> destination;
  destination.insert(3);

  destination = std::move(source);

  EXPECT_EQ(source.size(), 0);
  EXPECT_FALSE(source.contains(1));
  EXPECT_FALSE(source.contains(2));

  EXPECT_EQ(destination.size(), 3);
  EXPECT_TRUE(destination.contains(1));
  EXPECT_TRUE(destination.contains(2));
  EXPECT_FALSE(destination.contains(3));
}

TEST(MultisetTest, InsertMethod) {
  s21::multiset<int> test;
  test.insert(1);
  EXPECT_FALSE(test.empty());
  EXPECT_EQ(test.size(), 1);
  test.insert(2);
  EXPECT_EQ(test.size(), 2);
  test.insert(2);
  EXPECT_EQ(test.size(), 3);
  test.insert(2);
  EXPECT_EQ(test.size(), 4);
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};

  EXPECT_EQ(test_set.size(), 6);

  EXPECT_TRUE(test_set.contains(1));
  EXPECT_TRUE(test_set.contains(2));
  EXPECT_TRUE(test_set.contains(3));
  EXPECT_FALSE(test_set.contains(0));
  EXPECT_FALSE(test_set.contains(4));
}

TEST(MultisetTest, FindMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};

  auto it1 = test_set.find(1);
  auto it2 = test_set.find(2);
  auto it3 = test_set.find(3);
  auto it4 = test_set.find(4);

  EXPECT_NE(it1, test_set.end());
  EXPECT_NE(it2, test_set.end());
  EXPECT_NE(it3, test_set.end());
  EXPECT_EQ(it4, test_set.end());
}

TEST(MultisetTest, ContainsMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};

  EXPECT_TRUE(test_set.contains(1));
  EXPECT_TRUE(test_set.contains(2));
  EXPECT_TRUE(test_set.contains(3));
  EXPECT_FALSE(test_set.contains(0));
  EXPECT_FALSE(test_set.contains(4));
}

TEST(MultisetTest, BeginMethod) {
  s21::multiset<int> test_set;
  test_set.insert(1);
  test_set.insert(2);
  test_set.insert(3);
  int i = 1;
  for (auto it = test_set.begin(); it != test_set.end(); ++it, ++i) {
    EXPECT_EQ(*it, i);
  }
}

TEST(MultisetTest, SizeMethod) {
  s21::multiset<int> test_set;
  EXPECT_EQ(test_set.size(), 0);

  test_set.insert(1);
  test_set.insert(2);
  test_set.insert(2);
  test_set.insert(3);

  EXPECT_EQ(test_set.size(), 4);
}

TEST(MultisetTest, MaxSizeMethod) {
  s21::multiset<int> test_set;
  EXPECT_GE(test_set.max_size(), test_set.size());

  for (int i = 0; i < 1000; ++i) {
    test_set.insert(i);
  }

  EXPECT_GE(test_set.max_size(), test_set.size());
}

TEST(MultisetTest, ClearMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};
  EXPECT_EQ(test_set.size(), 6);

  test_set.clear();

  EXPECT_EQ(test_set.size(), 0);
  EXPECT_TRUE(test_set.empty());
}

TEST(MultisetTest, EraseMethod) {
  s21::multiset<int> test_set = {1, 2, 2, 3, 3, 3};
  EXPECT_EQ(test_set.size(), 6);

  auto it = test_set.find(2);
  test_set.erase(it);

  EXPECT_EQ(test_set.size(), 5);
}

TEST(MultisetTest, SwapMethod) {
  s21::multiset<int> test_set1 = {1, 2, 2, 3, 3, 3};
  s21::multiset<int> test_set2 = {4, 5, 6};

  EXPECT_EQ(test_set1.size(), 6);
  EXPECT_EQ(test_set2.size(), 3);

  test_set1.swap(test_set2);
  EXPECT_EQ(test_set1.size(), 3);
  EXPECT_EQ(test_set2.size(), 6);
  EXPECT_TRUE(test_set1.contains(4));
  EXPECT_TRUE(test_set2.contains(1));
}

TEST(MultisetTest, MergeMethod) {
  s21::multiset<int> test_set1 = {1, 2, 2, 3, 3, 3};
  s21::multiset<int> test_set2 = {4, 5, 6};

  test_set1.merge(test_set2);

  EXPECT_EQ(test_set1.size(), 9);

  EXPECT_TRUE(test_set2.empty());
}

TEST(MultisetTest, CountMethod) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 2, 4, 4, 4, 5};
  EXPECT_EQ(multiset.count(1), 1);
  EXPECT_EQ(multiset.count(2), 3);
  EXPECT_EQ(multiset.count(3), 1);
  EXPECT_EQ(multiset.count(4), 3);
  EXPECT_EQ(multiset.count(5), 1);
  EXPECT_EQ(multiset.count(6), 0);
}

TEST(MultisetTest, TestLowerBound) {
  s21::multiset<int> my = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto lb1 = my.lower_bound(2);
  EXPECT_EQ((*lb1).first, 2);
  auto lb2 = my.lower_bound(5);
  EXPECT_EQ(lb2, my.end());
  auto lb3 = my.lower_bound(0);
  EXPECT_EQ(lb3, my.begin());
}

TEST(MultisetTest, TestUpperBound) {
  s21::multiset<int> my = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  auto lb1 = my.upper_bound(1);
  EXPECT_EQ((*lb1).first, 2);
  auto lb2 = my.upper_bound(5);
  EXPECT_EQ(lb2, my.end());
  auto lb3 = my.upper_bound(0);
  EXPECT_EQ(lb3, my.begin());
}

TEST(MultisetTest, TestEqualRange) {
  s21::multiset<int> myMultiset = {1, 2, 2, 3, 4, 4, 5};
  auto range1 = myMultiset.equal_range(2);
  EXPECT_EQ(range1.first, myMultiset.lower_bound(2));
  auto ub1 = myMultiset.upper_bound(2);
  EXPECT_EQ(range1.second, ub1);

  auto range2 = myMultiset.equal_range(4);
  EXPECT_EQ(range2.first, myMultiset.lower_bound(4));
  auto ub2 = myMultiset.upper_bound(4);
  EXPECT_EQ(range2.second, ub2);
}

TEST(MultisetTest, InsertMany) {
  s21::multiset<int> test({1, 2, 3, 4, 5});
  test.insert_many(1, 2, 3, 4, 5);
  EXPECT_EQ(test.size(), 10);
  auto iter = test.end();
  --iter;
  EXPECT_EQ(*iter, 5);
  --iter;
  EXPECT_EQ(*iter, 5);
  --iter;
  EXPECT_EQ(*iter, 4);
  --iter;
  EXPECT_EQ(*iter, 4);
}

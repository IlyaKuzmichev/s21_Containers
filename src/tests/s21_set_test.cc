#include <gtest/gtest.h>

#include <set>
#include <utility>

#include "s21_containers.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> emptySet;
  EXPECT_TRUE(emptySet.empty());
}

TEST(SetTest, InitializerConstructor) {
  s21::set<int> initializedSet = {1, 2, 3};
  EXPECT_EQ(initializedSet.size(), 3);
  for (long unsigned int i = 1; i <= initializedSet.size(); i++) {
    EXPECT_TRUE(initializedSet.contains(i));
  }
  EXPECT_FALSE(initializedSet.contains(4));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> OrSet = {1, 2, 3};
  s21::set<int> Copy(OrSet);
  EXPECT_EQ(OrSet.size(), Copy.size());
  int i = 1;
  for (auto it = Copy.begin(); it != Copy.end(); it++, i++) {
  }
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> OrSet = {1, 2, 3};
  s21::set<int> Copy = std::move(OrSet);
  EXPECT_EQ(Copy.size(), 3);
  EXPECT_EQ(OrSet.size(), 0);
  int i = 1;
  for (auto it = Copy.begin(); it != Copy.end(); it++, i++) {
    EXPECT_EQ(*it, i);
  }
  EXPECT_TRUE(OrSet.empty());
}

TEST(SetTest, CopyAssignment) {
  s21::set<int> origin = {1, 2, 3};
  s21::set<int> copy = {4, 5, 6, 7, 8, 9};
  copy = origin;
  EXPECT_EQ(origin.size(), copy.size());
  auto j = 1;
  for (auto iter = copy.begin(); iter != copy.end(); ++iter, j++) {
    EXPECT_EQ(*iter, j);
  }
}

TEST(SetTest, MoveAssignment) {
  s21::set<int> origin = {1, 2, 3};
  s21::set<int> copy = {4, 5, 6, 7, 8, 9};
  copy = std::move(origin);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(copy.size(), 3);
  auto j = 1;
  for (auto iter = copy.begin(); iter != copy.end(); ++iter, j++) {
    EXPECT_EQ(*iter, j);
  }
}

TEST(SetTest, BeginEnd) {
  s21::set<int> mySet = {1, 2, 3, 4, 5};
  auto it = mySet.begin();
  int expectedValue = 1;
  while (it != mySet.end()) {
    EXPECT_EQ(*it, expectedValue);
    ++it;
    ++expectedValue;
  }
}

TEST(SetTest, Empty) {
  s21::set<int> emptySet;
  s21::set<int> nonEmptySet = {1, 2, 3};
  EXPECT_TRUE(emptySet.empty());
  EXPECT_FALSE(nonEmptySet.empty());
}

TEST(SetTest, setSize) {
  s21::set<int> emptyset;
  s21::set<double> setOfSize5 = {0, 1, 2, 3, 4};
  s21::set<int> setOfSize10 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(emptyset.size(), 0u);
  EXPECT_EQ(setOfSize5.size(), 5u);
  EXPECT_EQ(setOfSize10.size(), 10u);
}

TEST(SetTest, SizeAndMaxSize) {
  s21::set<int> mySet;
  EXPECT_EQ(mySet.size(), 0);
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);
  EXPECT_EQ(mySet.size(), 3);
  size_t maxSize = mySet.max_size();
  EXPECT_GE(maxSize, mySet.size());
}

TEST(SetTest, Insert) {
  std::pair<s21::set<int>::iterator, bool> result;
  s21::set<int> mySet;
  result = mySet.insert(42);
  result = mySet.insert(42);
  result = mySet.insert(10);
  EXPECT_TRUE(result.second);
  result = mySet.insert(20);
  EXPECT_TRUE(result.second);
}

TEST(SetTest, Erase) {
  s21::set<int> mySet;
  mySet.insert(1);
  mySet.insert(2);
  mySet.insert(3);
  mySet.insert(4);
  auto it = mySet.find(2);
  if (it != mySet.end()) {
    mySet.erase(it);
  }
  EXPECT_FALSE(mySet.find(2) != mySet.end());
  EXPECT_TRUE(mySet.find(1) != mySet.end());
  EXPECT_TRUE(mySet.find(3) != mySet.end());
  EXPECT_TRUE(mySet.find(4) != mySet.end());
}

TEST(SetTest, Swap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};
  set1.swap(set2);
  EXPECT_TRUE(set1.find(1) == set1.end());
  EXPECT_TRUE(set1.find(2) == set1.end());
  EXPECT_TRUE(set1.find(3) == set1.end());
  EXPECT_TRUE(set2.find(4) == set2.end());
  EXPECT_TRUE(set2.find(5) == set2.end());
  EXPECT_TRUE(set2.find(6) == set2.end());
}

TEST(SetTest, Merge) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};
  EXPECT_TRUE(set1.find(1) != set1.end());
  EXPECT_TRUE(set1.find(2) != set1.end());
  EXPECT_TRUE(set1.find(3) != set1.end());
  set1.merge(set2);
  EXPECT_FALSE(set1.empty());
  EXPECT_TRUE(set1.find(1) != set1.end());
  EXPECT_TRUE(set1.find(2) != set1.end());
  EXPECT_TRUE(set1.find(3) != set1.end());
  EXPECT_TRUE(set1.find(4) != set1.end());
  EXPECT_TRUE(set1.find(5) != set1.end());
}

TEST(SetTest, Find) {
  s21::set<int> mySet = {1, 2, 3, 4, 5};
  auto found1 = mySet.find(3);
  EXPECT_TRUE(found1 != mySet.end());
  auto found2 = mySet.find(6);
  EXPECT_TRUE(found2 == mySet.end());
}

TEST(SetTest, Contains) {
  s21::set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_TRUE(mySet.contains(3));
  EXPECT_FALSE(mySet.contains(6));
}

TEST(SetTest, InsertMany) {
  s21::set<int> test({1, 2, 3, 3, 3, 4, 5});
  auto result = test.insert_many(3, 6, 5, 3, 4, 7, 8, 8, 9, 10);
  EXPECT_EQ(test.size(), 10);
  EXPECT_FALSE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_FALSE(result[2].second);
  EXPECT_FALSE(result[3].second);
  EXPECT_FALSE(result[4].second);
  EXPECT_TRUE(result[5].second);
  auto iter = test.end();
  for (size_t i = test.size(); i > 0; --i) {
    --iter;
    EXPECT_EQ(*iter, i);
  }
}

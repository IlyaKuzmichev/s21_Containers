#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(TestMap, BasicConstructor) {
  s21::map<int, int> test;
  EXPECT_EQ(test.empty(), true);
}

TEST(TestMap, CopyConstructor) {
  s21::map<int, int> test1;
  test1.insert(1, 2);
  test1.insert(2, 3);
  test1.insert(3, 4);
  s21::map<int, int> test2(test1);
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
}

TEST(TestMap, InitializerListConstructor) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.empty(), false);
  EXPECT_EQ(test.at(1), 2);
  EXPECT_EQ(test.at(2), 3);
  EXPECT_EQ(test.at(3), 4);
  EXPECT_EQ(test.at(4), 5);
}

TEST(TestMap, MoveConstructor) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2(std::move(test1));
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
  EXPECT_EQ(test2.at(4), 5);
}

TEST(TestMap, AssignConstructor) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2 = test1;
  EXPECT_EQ(test2.at(1), 2);
  EXPECT_EQ(test2.at(2), 3);
  EXPECT_EQ(test2.at(3), 4);
  EXPECT_EQ(test2.at(4), 5);
  test1 = test2;
  test2 = std::move(test1);  // YEEEEEE ABOBAAA
}

TEST(TestMap, AtOneValue) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_EQ(test.at(1), 2);
}

TEST(TestMap, AtManyValue) {
  s21::map<int, int> test;
  test.insert(1, 2);
  test.insert(2, 3);
  test.insert(3, 4);
  test.insert(-1, 5);
  EXPECT_EQ(test.at(3), 4);
}

TEST(TestMap, AtError) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_THROW(test.at(2), std::out_of_range);
}

TEST(TestMap, SquareBracketsOne) {
  s21::map<int, int> test;
  test.insert(1, 2);
  EXPECT_EQ(test[1], 2);
}

TEST(TestMap, SquareBracketsMany) {
  s21::map<int, int> test;
  test.insert(1, 2);
  test.insert(2, 3);
  test.insert(3, 4);
  test.insert(-1, 5);
  EXPECT_EQ(test[3], 4);
  test[4] = 5;
  test[5] = 6;
  EXPECT_EQ(test[5], 6);
}

TEST(TestMap, BasicBegin) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ((*test.begin()).first, 1);
  EXPECT_EQ((*test.begin()).second, 2);
}

TEST(TestMap, BasicEnd) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ((*(--test.end())).first, 4);
  EXPECT_EQ((*(--test.end())).second, 5);
}

TEST(TestMap, BasicIterations) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  auto i = test.begin();
  EXPECT_EQ((*i).first, 1);
  EXPECT_EQ((*i).second, 2);
  i++;
  EXPECT_EQ((*i).first, 2);
  EXPECT_EQ((*i).second, 3);
  i++;
  EXPECT_EQ((*i).first, 3);
  EXPECT_EQ((*i).second, 4);
  i++;
  EXPECT_EQ((*i).first, 4);
  EXPECT_EQ((*i).second, 5);
}

TEST(TestMap, CapacityEmptyTrue) {
  s21::map<int, int> test;
  EXPECT_EQ(test.empty(), true);
}

TEST(TestMap, CapacityEmptyFalse) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.empty(), false);
}

TEST(TestMap, CapacitySizeZero) {
  s21::map<int, int> test;
  EXPECT_EQ(test.size(), 0);
}

TEST(TestMap, CapacitySizeMany) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.size(), 4);
}

TEST(TestMap, ModifiersClear) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.clear();
  EXPECT_EQ(test.size(), 0);
}

TEST(TestMap, ModifiersInsertValueType) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  auto pair = std::make_pair(9, 9);
  test.insert(pair);
  EXPECT_EQ(test[9], 9);
}

TEST(TestMap, ModifiersInsertKeyAndObj) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.insert(9, 9);
  EXPECT_EQ(test[9], 9);
}

TEST(TestMap, ModifiersInsertOrAssign) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.insert_or_assign(9, 9);
  EXPECT_EQ(test[9], 9);
  test.insert_or_assign(9, 10);
  EXPECT_EQ(test[9], 10);
}

TEST(TestMap, ModifiersErase) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.erase(test.begin());
  EXPECT_EQ(test.contains(1), false);
}

TEST(TestMap, ModifiersSwap) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2({{1, 10}, {2, 3}, {3, 4}, {4, 5}});
  test1.swap(test2);
  EXPECT_EQ(test1[1], 10);
  EXPECT_EQ(test2[1], 2);
}

TEST(TestMap, ModifiersMerge) {
  s21::map<int, int> test1({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  s21::map<int, int> test2({{5, 6}, {6, 7}});
  test1.merge(test2);
  EXPECT_EQ(test1.size(), 6);
  EXPECT_EQ(test1[1], 2);
  EXPECT_EQ(test1[5], 6);
  EXPECT_EQ(test1[6], 7);
}

TEST(TestMap, LookupContainsTrue) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.contains(1), true);
}

TEST(TestMap, LookupContainsFalse) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  EXPECT_EQ(test.contains(5), false);
}

TEST(TestMap, InsertMany) {
  s21::map<int, int> test({{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  test.insert_many(std::make_pair(5, 6), std::make_pair(7, 8),
                   std::make_pair(9, 10));
  EXPECT_EQ(test.size(), 7);
  EXPECT_EQ(test[5], 6);
  EXPECT_EQ(test[7], 8);
  EXPECT_EQ(test[9], 10);
  EXPECT_EQ(test[1], 2);
}

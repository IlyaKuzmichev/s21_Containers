#include <gtest/gtest.h>

#include <iostream>
#include <utility>

#include "s21_containers.h"

TEST(TestArray, BasicConstructor) {
  s21::array<int, 0> arr1;
  EXPECT_EQ(0, arr1.size());
}

TEST(TestArray, InitializerArrayConstructor) {
  s21::array<unsigned, 5> arr1({1, 2, 3, 4, 5});
  EXPECT_EQ(5, arr1.size());

  auto iter = arr1.begin();
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(i + 1, *iter);
    ++iter;
  }
}

TEST(TestArray, FailedInitializerList) {
  EXPECT_THROW((
    []{
      s21::array<unsigned, 5> arr1({1, 2, 3});
      (void)arr1;
    }()
  ), std::invalid_argument);
}

TEST(TestArray, CopyConstructor) {
  s21::array<int, 5> origin({5, 4, 3, 2, 1});
  s21::array cp(origin);

  EXPECT_EQ(origin.size(), cp.size());

  auto origin_iter = origin.begin();
  auto copy_iter = cp.begin();
  EXPECT_NE(origin_iter, copy_iter);
  for (; origin_iter != origin.end(); ++origin_iter, ++copy_iter) {
    EXPECT_EQ(*origin_iter, *copy_iter);
  }

  for (auto iter = cp.begin(); iter != cp.end(); ++iter) {
    *iter = 6;
  }

  for (auto iter = cp.begin(); iter != cp.end(); ++iter) {
    EXPECT_EQ(*iter, 6);
  }

  origin_iter = std::move(origin.begin());
  for (size_t i = 5; i > 0; --i, ++origin_iter) {
    EXPECT_EQ(i, *origin_iter);
  }
}

TEST(TestArray, MoveConstructor) {
  s21::array<double, 5> origin({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::array<double, 5> moved(std::move(origin));
  EXPECT_EQ(5ul, moved.size());
  EXPECT_EQ(5ul, origin.size());
  auto i = 1.1;
  for (auto iter = moved.begin(); iter != moved.end(); ++iter, i += 1.1) {
    EXPECT_DOUBLE_EQ(i, *iter);
  }
}

TEST(TestArray, MoveAssignment) {
  s21::array<int, 4> l({1, 2, 3, 4});
  s21::array<int, 4> origin({5, 6, 7, 8});

  l = std::move(origin);
  EXPECT_EQ(4, l.size());
  EXPECT_EQ(4, origin.size());

  auto i = 5;
  for (auto iter = l.begin(); iter != l.end(); ++iter, i++) {
    EXPECT_EQ(i, *iter);
  }

  auto j = 1;
  for (auto iter = origin.begin(); iter != origin.end(); ++iter, j++) {
    EXPECT_EQ(j, *iter);
  }
}

TEST(TestArray, CopyAssignment) {
  s21::array<int, 4> origin({1, 2, 3, 4});
  s21::array<int, 4> copy({5, 6, 7, 8});

  copy = origin;
  auto j = 1;
  for (auto iter = copy.begin(); iter != copy.end(); ++iter, j++) {
    EXPECT_EQ(j, *iter);
  }
}

TEST(TestArray, BeginEnd) {
  s21::array<char, 3> l1 = {'a', 'b', 'c'};
  auto it = l1.begin();
  ;
  std::string a = "abc";
  for (int i = 0; it != l1.end(); i++, it++) {
    EXPECT_EQ(a[i], *it);
  }
}

TEST(TestArray, Array_At) {
  try {
    std::array<int, 5> myArray = {1, 2, 3, 4, 5};
    int value = myArray.at(2);
    EXPECT_EQ(value, 3);
  } catch (const std::out_of_range& e) {
    EXPECT_EQ(e.what(), "array::at: __n (which is 63) >= _Nm (which is 5)");
  }
}

TEST(TestArray, ArrayEmpty) {
  s21::array<int, 0> emptyArray;
  s21::array<int, 5> nonEmptyArray = {1, 2, 3, 4, 5};
  EXPECT_TRUE(emptyArray.empty());
  EXPECT_FALSE(nonEmptyArray.empty());
}

TEST(TestArray, ArraySize) {
  s21::array<int, 0> emptyArray;
  s21::array<int, 5> arrayOfSize5;
  s21::array<int, 10> arrayOfSize10;
  EXPECT_EQ(emptyArray.size(), 0u);
  EXPECT_EQ(arrayOfSize5.size(), 5u);
  EXPECT_EQ(arrayOfSize10.size(), 10u);
}

TEST(TestArray, ArraySwap) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {10, 20, 30, 40, 50};

  s21::array<int, 5> arr1_copy = arr1;
  s21::array<int, 5> arr2_copy = arr2;

  arr1.swap(arr2);

  for (size_t i = 0; i < 5; i++) {
    EXPECT_EQ(arr1[i], arr2_copy[i]);
    EXPECT_EQ(arr2[i], arr1_copy[i]);
  }
}

TEST(TestArray, ArrayFill) {
  s21::array<int, 5> arr;
  int fillValue = 42;
  arr.fill(fillValue);
  for (size_t i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i], fillValue);
  }
}

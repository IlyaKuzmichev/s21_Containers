#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(TestQueue, BasicConstructor) {
  s21::queue<int> queue;

  EXPECT_EQ(queue.empty(), true);
  EXPECT_EQ(queue.size(), 0);
}

TEST(TestQueue, CopyConstructor) {
  s21::queue<int> queue1;
  queue1.push(1);
  s21::queue<int> queue2(queue1);
  queue2.pop();

  EXPECT_EQ(queue1.size(), 1);
  EXPECT_EQ(queue1.front(), 1);
  EXPECT_EQ(queue2.size(), 0);
}

TEST(TestQueue, MoveConstructor) {
  s21::queue<int> queue1;
  queue1.push(1);
  s21::queue<int> queue2(std::move(queue1));

  EXPECT_EQ(queue2.empty(), false);
  EXPECT_EQ(queue2.size(), 1);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue1.empty(), true);
}

TEST(TestQueue, OperatorOverloadMove) {
  s21::queue<int> queue1;
  queue1.push(1);
  s21::queue<int> queue2 = std::move(queue1);

  EXPECT_EQ(queue2.empty(), false);
  EXPECT_EQ(queue2.size(), 1);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue1.empty(), true);
}

TEST(TestQueue, InitializerListConstructor) {
  std::initializer_list<int> tmp{1, 2, 3};
  s21::queue<int> queue(tmp);

  EXPECT_EQ(queue.empty(), false);
  EXPECT_EQ(queue.size(), 3);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 3);
}

TEST(TestQueue, Front) {
  std::initializer_list<int> tmp{1, 2, 3};
  s21::queue<int> queue(tmp);

  EXPECT_EQ(queue.front(), 1);
}

TEST(TestQueue, Back) {
  std::initializer_list<int> tmp{1, 2, 3};
  s21::queue<int> queue(tmp);

  EXPECT_EQ(queue.back(), 3);
}

TEST(TestQueue, EmptyTrue) {
  s21::queue<int> queue;

  EXPECT_EQ(queue.empty(), true);
}

TEST(TestQueue, EmptyFalse) {
  s21::queue<int> queue;
  queue.push(1);

  EXPECT_EQ(queue.empty(), false);
}

TEST(TestQueue, SizeNull) {
  s21::queue<int> queue;

  EXPECT_EQ(queue.size(), 0);
}

TEST(TestQueue, Size) {
  std::initializer_list<int> tmp{1, 2, 3, 4, 5};
  s21::queue<int> queue(tmp);

  EXPECT_EQ(queue.size(), 5);
}

TEST(TestQueue, Push) {
  s21::queue<int> queue;
  queue.push(2);

  EXPECT_EQ(queue.front(), 2);
}

TEST(TestQueue, Pop) {
  s21::queue<int> queue;
  queue.push(2);
  queue.pop();

  EXPECT_EQ(queue.empty(), true);
}

TEST(TestQueue, Swap) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;
  queue1.push(2);
  queue1.swap(queue2);

  EXPECT_EQ(queue1.empty(), true);
  EXPECT_EQ(queue2.empty(), false);
  EXPECT_EQ(queue2.size(), 1);
  EXPECT_EQ(queue2.front(), 2);
}

TEST(TestQueue, InsertManyBackOnce) {
  s21::queue<int> queue({0, 1, 2});
  queue.insert_many_back(3);

  EXPECT_EQ(4, queue.size());

  for (int i = 0; i < 4; ++i, queue.pop()) {
    EXPECT_EQ(i, queue.front());
  }
}

TEST(TestQueue, InsertManyBackMultiple) {
  s21::queue<int> queue({0, 1, 4, 9});
  queue.insert_many_back(std::move(16), std::move(25), 36);

  EXPECT_EQ(7, queue.size());

  for (int i = 0; i < 7; ++i, queue.pop()) {
    EXPECT_EQ(i * i, queue.front());
  }
}

TEST(TestQueue, InsertManyBackNothing) {
  s21::queue<int> queue({1, 2, 3});
  queue.insert_many_back();

  EXPECT_EQ(3, queue.size());

  for (int i = 1; i < 4; ++i, queue.pop()) {
    EXPECT_EQ(i, queue.front());
  }
}

TEST(TestQueue, InsertManyBackEmpty) {
  s21::queue<int> queue;
  queue.insert_many_back(1, 2, 3);

  EXPECT_EQ(3, queue.size());

  for (int i = 1; i < 4; ++i, queue.pop()) {
    EXPECT_EQ(i, queue.front());
  }
}

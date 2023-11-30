#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(TestStack, BasicConstructor) {
  s21::stack<int> stack;

  EXPECT_EQ(stack.empty(), true);
  EXPECT_EQ(stack.size(), 0);
}

TEST(TestStack, CopyConstructor) {
  s21::stack<int> stack1;
  stack1.push(1);
  s21::stack<int> stack2(stack1);
  stack2.pop();

  EXPECT_EQ(stack1.size(), 1);
  EXPECT_EQ(stack1.top(), 1);
  EXPECT_EQ(stack2.size(), 0);
}

TEST(TestStack, MoveConstructor) {
  s21::stack<int> stack1;
  stack1.push(1);
  s21::stack<int> stack2(std::move(stack1));

  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.size(), 1);
  EXPECT_EQ(stack2.top(), 1);
  EXPECT_EQ(stack1.empty(), true);
}

TEST(TestStack, OperatorOverloadMove) {
  s21::stack<int> stack1;
  stack1.push(1);
  s21::stack<int> stack2 = std::move(stack1);

  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.size(), 1);
  EXPECT_EQ(stack2.top(), 1);
  EXPECT_EQ(stack1.empty(), true);
}

TEST(TestStack, InitializerListConstructor) {
  std::initializer_list<int> tmp{1, 2, 3};
  s21::stack<int> stack(tmp);

  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
  stack.pop();
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
  stack.pop();
  EXPECT_EQ(stack.empty(), true);
}

TEST(TestStack, Top) {
  std::initializer_list<int> tmp{1, 2, 3};
  s21::stack<int> stack(tmp);

  EXPECT_EQ(stack.top(), 3);
}

TEST(TestStack, EmptyTrue) {
  s21::stack<int> stack;

  EXPECT_EQ(stack.empty(), true);
}

TEST(TestStack, EmptyFalse) {
  s21::stack<int> stack;
  stack.push(1);

  EXPECT_EQ(stack.empty(), false);
}

TEST(TestStack, SizeNull) {
  s21::stack<int> stack;

  EXPECT_EQ(stack.size(), 0);
}

TEST(TestStack, Size) {
  std::initializer_list<int> tmp{1, 2, 3, 4, 5};
  s21::stack<int> stack(tmp);

  EXPECT_EQ(stack.size(), 5);
}

TEST(TestStack, Push) {
  s21::stack<int> stack;
  stack.push(2);

  EXPECT_EQ(stack.top(), 2);
}

TEST(TestStack, Pop) {
  s21::stack<int> stack;
  stack.push(2);
  stack.push(3);
  stack.pop();

  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stack.top(), 2);
}

TEST(TestStack, Swap) {
  s21::stack<int> stack1;
  s21::stack<int> stack2;
  stack1.push(2);
  stack1.swap(stack2);

  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.size(), 1);
  EXPECT_EQ(stack2.top(), 2);
}

TEST(TestStack, InsertManyFrontOnce) {
  s21::stack<int> stack({0, 2, 4, 6});
  stack.insert_many_front(8);

  EXPECT_EQ(5, stack.size());
  for (int i = 4; i >= 0; --i, stack.pop()) {
    EXPECT_EQ(2 * i, stack.top());
  }
}

TEST(TestStack, InsertManyFrontMultiple) {
  s21::stack<int> stack({0, 1, 4, 9});
  stack.insert_many_front(std::move(16), std::move(25), 36);

  EXPECT_EQ(7, stack.size());
  for (int i = 6; i >= 0; --i, stack.pop()) {
    EXPECT_EQ(i * i, stack.top());
  }
}

TEST(TestStack, InsertManyFrontNothing) {
  s21::stack<int> stack({1, 2, 3});
  stack.insert_many_front();

  EXPECT_EQ(3, stack.size());
  for (int i = 3; i > 0; --i, stack.pop()) {
    EXPECT_EQ(i, stack.top());
  }
}

TEST(TestStack, InsertManyFrontEmpty) {
  s21::stack<int> stack;
  stack.insert_many_front(1, 2, 3);

  EXPECT_EQ(3, stack.size());
  for (int i = 3; i > 0; --i, stack.pop()) {
    EXPECT_EQ(i, stack.top());
  }
}

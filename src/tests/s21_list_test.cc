#include <gtest/gtest.h>

#include <utility>

#include "s21_containers.h"

TEST(TestList, BasicConstructor) {
  s21::list<int> l;
  EXPECT_EQ(0, l.size());
}

TEST(TestList, SizeConstructor) {
  s21::list<double> l(24);
  EXPECT_EQ(24, l.size());
  for (auto iter = l.begin(); iter != l.end(); ++iter) {
    EXPECT_DOUBLE_EQ(0, *iter);
  }
}

TEST(TestList, InitializerListConstructor) {
  s21::list<unsigned> l({1, 2, 3, 4, 5});
  EXPECT_EQ(5, l.size());

  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i) {
    EXPECT_EQ(i + 1, *iter);
    ++iter;
  }
}

TEST(TestList, CopyConstructor) {
  s21::list<int> origin({5, 4, 3, 2, 1});
  s21::list<int> cp(origin);

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

TEST(TestList, MoveConstructor) {
  s21::list<double> origin({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::list<double> moved(std::move(origin));

  EXPECT_EQ(5, moved.size());
  EXPECT_EQ(0, origin.size());

  auto i = 1;
  for (auto iter = moved.begin(); iter != moved.end(); ++iter, ++i) {
    EXPECT_DOUBLE_EQ(i * 1.1, *iter);
  }
}

TEST(TestList, CopyAssignment) {
  s21::list<int> l({1, 2, 3});
  s21::list<int> origin({4, 5, 6, 7});

  l = origin;

  EXPECT_EQ(origin.size(), l.size());

  for (auto iter = l.begin(), oriter = origin.begin(); iter != l.end();
       ++iter, ++oriter) {
    EXPECT_EQ(*oriter, *iter);
  }
}

TEST(TestList, MoveAssignment) {
  s21::list<int> l({1, 2, 3});
  s21::list<int> origin({4, 5, 6, 7});

  l = std::move(origin);

  EXPECT_EQ(4, l.size());
  EXPECT_EQ(0, origin.size());

  auto i = 4;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, InitializerListAssignment) {
  s21::list<int> l(25);

  l = {1, 2, 3, 4, 5};

  EXPECT_EQ(5, l.size());

  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, Front) {
  s21::list<char> l({'a', 'b', 'c'});
  EXPECT_EQ('a', l.front());

  s21::list<double> l2({5.5});
  EXPECT_DOUBLE_EQ(5.5, l2.front());

  s21::list<std::string> l3({"hello", "my", "precious", "world"});
  EXPECT_EQ("hello", l3.front());
}

TEST(TestList, Back) {
  s21::list<char> l({'a', 'b', 'c'});
  EXPECT_EQ('c', l.back());

  s21::list<double> l2({5.5});
  EXPECT_DOUBLE_EQ(5.5, l2.back());

  s21::list<std::string> l3({"hello", "my", "precious", "world"});
  EXPECT_EQ("world", l3.back());
}

TEST(TestList, Iterator) {
  s21::list<int> l({2, 4, 6, 8, 10, 12, 14});
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(2 * i, *iter);
  }
  EXPECT_EQ(8, i);

  i = 1;
  for (auto iter = l.cbegin(); iter != l.cend(); ++iter, ++i) {
    EXPECT_EQ(2 * i, *iter);
  }
  EXPECT_EQ(8, i);
}

TEST(TestList, Clear) {
  s21::list<char> l(10000);
  l.clear();
  EXPECT_EQ(0, l.size());
}

TEST(TestList, Insert) {
  s21::list<char> l({'b', 'b'});
  auto iter = l.insert(l.begin(), 'a');
  ++iter;
  ++iter;
  iter = l.insert(iter, 'o');
  l.insert(l.end(), 'a');

  EXPECT_EQ(5, l.size());
  std::string text = "aboba";
  auto i = 0;
  for (iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, Erase) {
  s21::list<char> l({'x', 'a', 'r', 'b', 'o', 'b', 'r', 'a'});
  auto iter = l.begin();
  l.erase(iter);
  iter = l.begin();
  ++iter;
  l.erase(iter);
  iter = l.end();
  iter--;
  --iter;
  l.erase(iter);

  EXPECT_EQ(5, l.size());
  std::string text = "aboba";
  auto i = 0;
  for (iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, PushBack) {
  s21::list<int> l;

  for (int i = 0; i < 100; ++i) {
    l.push_back(i);
  }

  EXPECT_EQ(100, l.size());

  int i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, PopBack) {
  s21::list<char> l(10000);

  for (size_t i = 0; i < 7000; ++i) {
    l.pop_back();
  }

  EXPECT_EQ(3000, l.size());

  for (size_t i = 0; i < 3000; ++i) {
    l.pop_back();
  }
  EXPECT_EQ(0, l.size());
}

TEST(TestList, PushFront) {
  s21::list<int> l;

  for (int i = 0; i < 100; ++i) {
    l.push_front(i);
  }

  EXPECT_EQ(100, l.size());

  int i = 99;
  for (auto iter = l.begin(); iter != l.end(); ++iter, --i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, Swap) {
  s21::list<int> l1({1, 2, 3});
  s21::list<int> l2({4, 5, 6, 7});

  l1.swap(l2);

  EXPECT_EQ(4, l1.size());
  EXPECT_EQ(3, l2.size());

  auto iter = l2.begin();
  for (int i = 1; i <= 3; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }

  iter = l1.begin();
  for (int i = 4; i <= 7; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, SelfSwap) {
  s21::list<int> l({1, 2, 3, 4});

  l.swap(l);

  EXPECT_EQ(4, l.size());

  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, MergeFullOrdered) {
  s21::list<int> l1({1, 2, 3, 4});
  s21::list<int> l2({5, 6, 7, 8});

  l1.merge(l2);

  EXPECT_EQ(8, l1.size());
  EXPECT_EQ(0, l2.size());

  auto iter = l1.begin();
  for (int i = 1; i < 9; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, MergeReversed) {
  s21::list<int> l1({5, 6, 7, 8});
  s21::list<int> l2({1, 2, 3, 4});

  l1.merge(l2);

  EXPECT_EQ(8, l1.size());
  EXPECT_EQ(0, l2.size());

  auto iter = l1.begin();
  for (int i = 1; i < 9; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, MergeShuffled) {
  s21::list<int> l1({2, 3, 4, 7});
  s21::list<int> l2({1, 5, 6, 8});

  l1.merge(l2);

  EXPECT_EQ(8, l1.size());
  EXPECT_EQ(0, l2.size());

  auto iter = l1.begin();
  for (int i = 1; i < 9; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, MergeEmptyRight) {
  s21::list<int> l1({1, 2, 3, 4, 5, 6, 7, 8});
  s21::list<int> l2;

  l1.merge(l2);

  EXPECT_EQ(8, l1.size());
  EXPECT_EQ(0, l2.size());

  auto iter = l1.begin();
  for (int i = 1; i < 9; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, MergeEmptyLeft) {
  s21::list<unsigned> l1;
  s21::list<unsigned> l2({1, 2, 3, 4, 5, 6, 7, 8});

  l1.merge(l2);

  EXPECT_EQ(8, l1.size());
  EXPECT_EQ(0, l2.size());

  auto iter = l1.begin();
  for (unsigned i = 1; i < 9; ++i, ++iter) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, SpliceFront) {
  s21::list<char> l1({'o', 'b', 'u', 's'});
  s21::list<char> l2({'a', 'b'});

  l1.splice(l1.begin(), l2);

  EXPECT_EQ(6, l1.size());
  EXPECT_EQ(0, l2.size());

  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l1.begin(); iter != l1.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, SpliceBack) {
  s21::list<char> l1({'a', 'b', 'o'});
  s21::list<char> l2({'b', 'u', 's'});

  l1.splice(l1.end(), l2);

  EXPECT_EQ(6, l1.size());
  EXPECT_EQ(0, l2.size());

  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l1.begin(); iter != l1.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, SpliceMiddle) {
  s21::list<char> l1({'a', 's'});
  s21::list<char> l2({'b', 'o', 'b', 'u'});

  auto iter = l1.begin();
  ++iter;

  l1.splice(iter, l2);

  EXPECT_EQ(6, l1.size());
  EXPECT_EQ(0, l2.size());

  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l1.begin(); iter != l1.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, SpliceEmptyRight) {
  s21::list<char> l1({'a', 'b', 'o', 'b', 'u', 's'});
  s21::list<char> l2;

  auto iter = l1.begin();
  ++iter;

  l1.splice(iter, l2);

  EXPECT_EQ(6, l1.size());
  EXPECT_EQ(0, l2.size());

  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l1.begin(); iter != l1.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, SpliceEmptyLeft) {
  s21::list<char> l1;
  s21::list<char> l2({'a', 'b', 'o', 'b', 'u', 's'});

  l1.splice(l1.begin(), l2);

  EXPECT_EQ(6, l1.size());
  EXPECT_EQ(0, l2.size());

  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l1.begin(); iter != l1.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, ReverseEmpty) {
  s21::list<char> l;

  l.reverse();

  EXPECT_EQ(0, l.size());
}

TEST(TestList, Reverse) {
  s21::list<char> l({'O', 'B', 'U', 'C', 'A', 'P', 'K'});

  l.reverse();

  EXPECT_EQ(7, l.size());

  std::string text = "KPACUBO";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, UniqueNOOP) {
  s21::list<char> l({'a', 'b', 'o', 'b', 'u', 's'});

  l.unique();

  EXPECT_EQ(6, l.size());
  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, Unique) {
  s21::list<char> l({'a', 'a', 'a', 'b', 'b', 'o', 'b', 'u', 's', 's', 's'});

  l.unique();

  EXPECT_EQ(6, l.size());
  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, SortAlreadySorted) {
  s21::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

  l.sort();

  EXPECT_EQ(10, l.size());
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, SortReversed) {
  s21::list<int> l({10, 9, 8, 7, 6, 5, 4, 3, 2, 1});

  l.sort();

  EXPECT_EQ(10, l.size());
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, SortShuffled) {
  s21::list<int> l({5, 6, 4, 10, 8, 2, 3, 7, 9, 1});

  l.sort();

  EXPECT_EQ(10, l.size());
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, SortEmpty) {
  s21::list<std::string> l;

  l.sort();

  EXPECT_EQ(0, l.size());
}

TEST(TestList, SortZeroValues) {
  s21::list<double> l(10000);

  l.sort();

  EXPECT_EQ(10000, l.size());

  for (auto iter = l.begin(); iter != l.end(); ++iter) {
    EXPECT_DOUBLE_EQ(0, *iter);
  }
}

TEST(TestList, InsertManyOnce) {
  s21::list<int> l({1, 2, 3});

  auto pos = l.begin();
  ++pos;
  pos = l.insert_many(pos, 4);

  EXPECT_EQ(4, *pos);

  EXPECT_EQ(4, l.size());

  int arr[] = {1, 4, 2, 3};
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(arr[i], *iter);
  }
}

TEST(TestList, InsertManyMultiple) {
  s21::list<char> l({'a', 'b', 'c'});

  auto pos = l.begin();
  ++pos;
  ++pos;
  pos = l.insert_many(pos, 'd', 'e', 'f');

  EXPECT_EQ(*pos, 'd');

  EXPECT_EQ(6, l.size());

  char arr[] = {'a', 'b', 'd', 'e', 'f', 'c'};
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(arr[i], *iter);
  }

  pos = l.insert_many(l.begin(), 'a', 'b', std::move('o'), 'b', 'a');

  EXPECT_EQ(*pos, 'a');

  char extended_arr[] = {'a', 'b', 'o', 'b', 'a', 'a', 'b', 'd', 'e', 'f', 'c'};
  i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(extended_arr[i], *iter);
  }
}

TEST(TestList, InsertManyNothing) {
  s21::list<double> l({1.1, 2.2, 3.3});
  auto pos = l.insert_many(l.begin());

  EXPECT_DOUBLE_EQ(*pos, 1.1);

  EXPECT_EQ(3, l.size());
  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_DOUBLE_EQ(i * 1.1, *iter);
  }
}

TEST(TestList, InsertManyToEmpty) {
  s21::list<int> l;
  auto pos = l.insert_many(l.begin(), 1, 2, 3);

  EXPECT_EQ(*pos, 1);
  EXPECT_EQ(3, l.size());

  int i = 1;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(i, *iter);
  }
}

TEST(TestList, InsertManyToEnd) {
  s21::list<char> l({'a', 'b', 'o'});
  auto pos = l.insert_many(l.end(), 'b', 'u', 's');
  EXPECT_EQ(*pos, 'b');

  EXPECT_EQ(6, l.size());
  std::string text = "abobus";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, InsertManyBackOnce) {
  s21::list<int> l({0, 2, 4, 6});
  l.insert_many_back(8);

  EXPECT_EQ(5, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(2 * i, *iter);
  }
}

TEST(TestList, InsertManyBackMultiple) {
  s21::list<int> l({0, 1, 4, 9});
  l.insert_many_back(std::move(16), std::move(25), 36);

  EXPECT_EQ(7, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(i * i, *iter);
  }
}

TEST(TestList, InsertManyBackNothing) {
  s21::list<char> l({'c', 'o', 'o', 'l'});
  l.insert_many_back();

  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, InsertManyBackEmpty) {
  s21::list<char> l;
  l.insert_many_back('c', 'o', 'o', 'l');

  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, InsertManyFrontOnce) {
  s21::list<int> l({2, 4, 6, 8});
  l.insert_many_front(0);

  EXPECT_EQ(5, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(2 * i, *iter);
  }
}

TEST(TestList, InsertManyFrontMultiple) {
  s21::list<int> l({9, 16, 25, 36});
  l.insert_many_front(std::move(0), std::move(1), 4);

  EXPECT_EQ(7, l.size());
  auto iter = l.begin();
  for (size_t i = 0; i < l.size(); ++i, ++iter) {
    EXPECT_EQ(i * i, *iter);
  }
}

TEST(TestList, InsertManyFrontNothing) {
  s21::list<char> l({'c', 'o', 'o', 'l'});
  l.insert_many_front();

  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); ++iter, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

TEST(TestList, InsertManyFrontEmpty) {
  s21::list<char> l;
  l.insert_many_front('c', 'o', 'o', 'l');

  EXPECT_EQ(4, l.size());
  std::string text = "cool";
  size_t i = 0;
  for (auto iter = l.begin(); iter != l.end(); iter++, ++i) {
    EXPECT_EQ(text[i], *iter);
  }
}

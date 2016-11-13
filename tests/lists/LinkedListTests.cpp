#include "lists/LinkedList.h"
#include <gtest/gtest.h>

using namespace ds;
using namespace utils;

class LinkedListTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    v1.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
  }

  // virtual void TearDown() {}

  ds::LinkedList<int> v0{};
  ds::LinkedList<int> v1{};
  ds::LinkedList<int> v2{};
};

TEST_F(LinkedListTests, InitVec) { ASSERT_EQ(0, v0.size()); }

TEST_F(LinkedListTests, PushBackTests) {
  ASSERT_EQ(1, v1.size());
  ASSERT_EQ(1, v1.at(0));
  ASSERT_EQ(1, v1.front());
  ASSERT_EQ(1, v1.back());
  ASSERT_EQ(1, v1[0]);

  ASSERT_EQ(2, v2.size());
  ASSERT_EQ(2, v2.at(0));
  ASSERT_EQ(3, v2.at(1));
  ASSERT_EQ(3, v2[1]);
}

TEST_F(LinkedListTests, InsertTests) {
  v0.insert(1, 0);
  ASSERT_EQ(1, v0.at(0));
  v1.prepend(5);
  ASSERT_EQ(5, v1.at(0));
  EXPECT_EQ(2, v1.size());

  v2.insert(4, 1);
  EXPECT_EQ(3, v2.at(2));
  EXPECT_EQ(4, v2.at(1));
  EXPECT_EQ(3, v2.size());
}

TEST_F(LinkedListTests, DeleteTests) {

  v0.insert(1, 0);
  EXPECT_EQ(1, v0.pop());
  EXPECT_EQ(0, v0.size());
  EXPECT_EQ(true, v0.empty());

  v1.prepend(5);
  EXPECT_EQ(5, v1.deleteAt(0));
  EXPECT_EQ(1, v1.at(0));
  EXPECT_EQ(1, v1.size());

  v2.insert(4, 1);
  EXPECT_EQ(4, v2.deleteAt(1));
  EXPECT_EQ(3, v2.at(1));
  EXPECT_EQ(2, v2.at(0));
  EXPECT_EQ(2, v2.size());

  v2.clear();
  EXPECT_EQ(0, v2.size());
}

TEST_F(LinkedListTests, NegativeTests) {
  ASSERT_THROW(v0.at(1), std::out_of_range);
  ASSERT_THROW(v0[3], std::out_of_range);
  ASSERT_THROW(v0.pop(), std::out_of_range);
  ASSERT_THROW(v1.at(-1), std::out_of_range);
  ASSERT_THROW(v1.deleteAt(1000), std::out_of_range);
  ASSERT_THROW(v2.insert(1, 100), std::out_of_range);
}

TEST_F(LinkedListTests, ReverseTests) {
  v2.push_back(10);
  v2.reverse();
  EXPECT_EQ(10, v2[0]);
  EXPECT_EQ(3, v2[1]);
  EXPECT_EQ(2, v2[2]);
}

struct TestObj {
  int a, b, c;
};

TEST(GenericLinkedListTest, AllTests) {
  LinkedList<TestObj> TestLinkedList;

  TestObj test;
  test.a = 10;
  test.b = 11;
  test.c = 12;
  TestLinkedList.push_back(test);

  TestObj test2;
  test2.a = 15;
  test2.b = 16;
  test2.c = 17;
  TestLinkedList.push_back(test2);

  TestLinkedList.reverse();
  EXPECT_EQ(15, TestLinkedList[0].a);
  TestLinkedList.reverse();

  TestLinkedList.push_back(test);

  EXPECT_EQ(3, TestLinkedList.size());

  EXPECT_EQ(10, TestLinkedList[0].a);
  EXPECT_EQ(16, TestLinkedList[1].b);
  EXPECT_EQ(12, TestLinkedList[2].c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

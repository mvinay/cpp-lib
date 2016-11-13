#include "stack/Stack.h"
#include <gtest/gtest.h>

using namespace ds;
using namespace utils;

class StackTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    v1.push(1);
    v2.push(2);
    v2.push(3);
  }

  // virtual void TearDown() {}

  ds::Stack<int> v0{};
  ds::Stack<int> v1{};
  ds::Stack<int> v2{};
};

TEST_F(StackTests, InitTests) {
  EXPECT_EQ(0, v0.size());
  EXPECT_EQ(1, v1.size());
  EXPECT_EQ(2, v2.size());

  EXPECT_EQ(1, v1.peek());
  EXPECT_EQ(3, v2.peek());

  EXPECT_EQ(true, v0.empty());
  EXPECT_EQ(false, v1.empty());

  v1.clear();
  EXPECT_EQ(true, v1.empty());
}

TEST_F(StackTests, PopTests) {
  EXPECT_EQ(1, v1.pop());
  EXPECT_EQ(true, v1.empty());

  EXPECT_EQ(3, v2.pop());
  EXPECT_EQ(2, v2.pop());
  EXPECT_EQ(true, v2.empty());
}

struct TestObj {

  int a;
  float b;
  char c;

  TestObj(int _a, float _b, char _c) : a(_a), b(_b), c(_c) {}
};

TEST(GenericStackTests, AllTests) {
  TestObj t1(10, 11.1f, 'a');
  TestObj t2(11, 12.1f, 'b');

  Stack<TestObj> genericStack;

  genericStack.push(t1);
  EXPECT_EQ(10, genericStack.peek().a);

  genericStack.push(t2);
  EXPECT_EQ(11, genericStack.peek().a);
  EXPECT_EQ(2, genericStack.size());

  genericStack.pop();
  EXPECT_EQ(10, genericStack.peek().a);

  genericStack.clear();
  EXPECT_EQ(0, genericStack.size());
  EXPECT_EQ(true, genericStack.empty());
}

TEST_F(StackTests, NegativeTests) { ASSERT_THROW(v0.pop(), std::out_of_range); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

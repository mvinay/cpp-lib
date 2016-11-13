#include "queue/Queue.h"
#include <gtest/gtest.h>

using namespace ds;
using namespace utils;

class QueueTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    v1.push(1);
    v2.push(2);
    v2.push(3);
  }

  // virtual void TearDown() {}

  ds::Queue<int> v0{};
  ds::Queue<int> v1{};
  ds::Queue<int> v2{};
};

TEST_F(QueueTests, InitTests) {
  EXPECT_EQ(0, v0.size());
  EXPECT_EQ(1, v1.size());
  EXPECT_EQ(2, v2.size());

  EXPECT_EQ(1, v1.peek());
  EXPECT_EQ(2, v2.peek());

  EXPECT_EQ(true, v0.empty());
  EXPECT_EQ(false, v1.empty());

  v1.clear();
  EXPECT_EQ(true, v1.empty());
}

TEST_F(QueueTests, PopTests) {
  EXPECT_EQ(1, v1.pop());
  EXPECT_EQ(true, v1.empty());

  EXPECT_EQ(2, v2.pop());
  EXPECT_EQ(3, v2.pop());
  EXPECT_EQ(true, v2.empty());
}

struct TestObj {

  int a;
  float b;
  char c;

  TestObj(int _a, float _b, char _c) : a(_a), b(_b), c(_c) {}
};

TEST(GenericQueueTests, AllTests) {
  TestObj t1(10, 11.1f, 'a');
  TestObj t2(11, 12.1f, 'b');

  Queue<TestObj> genericQueue;

  genericQueue.push(t1);
  EXPECT_EQ(10, genericQueue.peek().a);

  genericQueue.push(t2);
  EXPECT_EQ(10, genericQueue.peek().a);
  EXPECT_EQ(2, genericQueue.size());

  genericQueue.pop();
  EXPECT_EQ(11, genericQueue.peek().a);

  genericQueue.clear();
  EXPECT_EQ(0, genericQueue.size());
  EXPECT_EQ(true, genericQueue.empty());
}

TEST_F(QueueTests, NegativeTests) { ASSERT_THROW(v0.pop(), std::out_of_range); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

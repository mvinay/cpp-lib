#include "arrays/Vector.h"
#include <gtest/gtest.h>

using namespace ds;

class VectorTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    v1.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
  }

  // virtual void TearDown() {}

  ds::Vector<int> v0{};
  ds::Vector<int> v1{};
  ds::Vector<int> v2{};
};

TEST_F(VectorTests, InitVec) { ASSERT_EQ(0, v0.size()); }

TEST_F(VectorTests, PushBackTests) {
  ASSERT_EQ(1, v1.size());
  ASSERT_EQ(1, v1.at(0));
  ASSERT_EQ(1, v1[0]);

  ASSERT_EQ(2, v2.size());
  ASSERT_EQ(2, v2.at(0));
  ASSERT_EQ(3, v2.at(1));
  ASSERT_EQ(3, v2[1]);
}

TEST_F(VectorTests, InsertTests) {

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

TEST_F(VectorTests, DeleteTests) {

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
}

TEST_F(VectorTests, FindAndRemoveTests) {
  v0.push_back(4);
  v0.push_back(3);

  EXPECT_EQ(1, v0.find(3));

  v0.prepend(3);

  v0.remove(3);

  EXPECT_EQ(1, v0.size());
  EXPECT_EQ(4, v0.at(0));
}

TEST_F(VectorTests, CapacityTests) {
  EXPECT_EQ(true, (v1.capacity() > v1.size()));

  v2.resize(100);
  EXPECT_EQ(100, v2.capacity());
}

TEST_F(VectorTests, NegativeTests) {
  ASSERT_DEATH({ v0.at(1); }, "Array Index Out of Bounds: 1");
  ASSERT_DEATH({ v0[3]; }, "Array Index Out of Bounds: 3");
  ASSERT_DEATH({ v0.pop(); }, "Array Index Out of Bounds: 0");
  ASSERT_DEATH({ v1.at(-1); }, "Array Index Out of Bounds: -1");
  ASSERT_DEATH({ v1.deleteAt(1000); }, "Array Index Out of Bounds: 1000");
  ASSERT_DEATH({ v2.insert(1, 100); }, "Array Index Out of Bounds: 100");
  ASSERT_DEATH({ v2.resize(1); },
               "new capacity should not delete existing elements");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "threadsafe";
  return RUN_ALL_TESTS();
}

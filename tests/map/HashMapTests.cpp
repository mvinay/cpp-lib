#include "map/HashMap.h"
#include <gtest/gtest.h>

using namespace ds;

class HashMapTests : public ::testing::Test {
protected:
  virtual void SetUp() { v1.put(256, 'a'); }

  // virtual void TearDown() {}

  ds::HashMap<int, char> v0{};
  ds::HashMap<int, char> v1{};
  ds::HashMap<int, char> v2{};
};

TEST_F(HashMapTests, InitTests) {
  EXPECT_EQ(0, v0.size());
  EXPECT_EQ(1, v1.size());
  EXPECT_EQ(0, v2.size());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

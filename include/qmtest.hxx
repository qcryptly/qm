#pragma once

#include <gtest/gtest.h>

namespace QM {

// The fixture for testing class Foo.
class Test : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  // You can do set-up work for each test here.
  //MainTest() {}

  // You can do clean-up work that doesn't throw exceptions here.
  //~MainTest() override {}

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  // Code here will be called immediately after the constructor (right
  // before each test).
  //void SetUp() override {}

  // Code here will be called immediately after each test (right
  // before the destructor).
  //void TearDown() override {}
};

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <utils/logger.hh>

#include <gtest/gtest.h>

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  logger::Init();

  return RUN_ALL_TESTS();
}

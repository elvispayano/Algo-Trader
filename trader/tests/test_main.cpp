#include <gtest/gtest.h>
#include "test_main.h"

void test_main(void) {
  ::testing::InitGoogleTest();
  RUN_ALL_TESTS();
}

#include <gtest/gtest.h>
#include "test_main.h"

#include "test_activation.cc"
#include "test_matrix.cc"

void test_main(void) {
  ::testing::InitGoogleTest();
  RUN_ALL_TESTS();
}

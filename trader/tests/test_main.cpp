/*
  Title:
    Test Main

  Description:
    This function implements Google Test and runs all tests that are found within
    project.

  Author:
    Elvis Payano
*/

#include <gtest/gtest.h>
#include "test_main.h"

void test_main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
}

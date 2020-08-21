/*
  Title:
    Test Main

  Description:
    This function implements Google Test and runs all tests that are found
    within project.

  Author:
    Elvis Payano
*/

#include "test_main.h"
#include <gtest/gtest.h>

void test_main( int argc, char** argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  RUN_ALL_TESTS();
}

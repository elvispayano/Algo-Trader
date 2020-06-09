#include <gtest/gtest.h>
#include "test_main.h"

#include "test_activation.cc"
#include "test_fully_connected_layer.cc"
#include "test_layer_base.cc"
#include "test_matrix.cc"
#include "test_neural_network.cc"
#include "test_utl_math.cc"

void test_main(void) {
  ::testing::InitGoogleTest();
  RUN_ALL_TESTS();
}

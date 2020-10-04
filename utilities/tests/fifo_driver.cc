/// FIFO Driver Unit Test
///
/// This unit test will test functionality of the created FIFO driver library.
///
/// \author   Elvis Payano
/// \date     04/10/2020
/// \version  0.0.1

// Utility Includes
#include "fifo_driver.h"
#include "utilities/random_number.h"

// Google Test Includes
#include "gtest/gtest.h"

class FIFODriverTest : public ::testing::Test {
protected:
  FIFODriverTest( void ) {
    rng   = 0;
    pPort = 0;
  }
  ~FIFODriverTest( void ) {
    rng   = 0;
    pPort = 0;
  }

  void SetUp( void ) override {
    rng   = new RandomNumber();
    pPort = new FIFODriver<int>;
  }
  void TearDown( void ) override {
    if ( rng )
      delete rng;

    if ( pPort )
      delete pPort;
  }

public:
  RandomNumber*    rng;
  FIFODriver<int>* pPort;
};

TEST_F( FIFODriverTest, temp ) {

  FAIL();
}

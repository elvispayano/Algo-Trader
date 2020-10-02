#include "comms/fc_layer_msg.h"

#include "utilities/random_number.h"

#include <gtest/gtest.h>

class FCLayerMsgTest : public ::testing::Test {
protected:
  FCLayerMsgTest( void ) {
    in   = new FCLayer();
    out  = new FCLayer();
    hold = new LayerMsg();
    rng  = new RandomNumber();
  }

  ~FCLayerMsgTest( void ) {
    if ( in )
      delete in;

    if ( out )
      delete out;

    if ( hold )
      delete hold;

    if ( rng )
      delete rng;
  }

public:
  LayerMsg* hold;
  FCLayer*  in;
  FCLayer*  out;

  RandomNumber* rng;
};

TEST_F( FCLayerMsgTest, Activation ) {

  in->activation = rng->activation();
  in->encode( *hold );
  out->decode( *hold );

  EXPECT_EQ( in->activation, out->activation );
  EXPECT_NE( in->activation, ActivationTypes::UNKNOWN );
  EXPECT_NE( out->activation, ActivationTypes::UNKNOWN );
}

TEST_F( FCLayerMsgTest, Row ) {
  in->row = rng->random( 300, 1000 );
  in->encode( *hold );
  out->decode( *hold );

  EXPECT_EQ( in->row, out->row );
  EXPECT_NE( in->row, 0 );
  EXPECT_NE( out->row, 0 );
}

TEST_F( FCLayerMsgTest, RowMax ) {
  in->rowMax = rng->random( 300, 1000 );
  in->encode( *hold );
  out->decode( *hold );

  EXPECT_EQ( in->rowMax, out->rowMax );
  EXPECT_NE( in->rowMax, 0 );
  EXPECT_NE( out->rowMax, 0 );
}

TEST_F( FCLayerMsgTest, Col ) {
  in->col = rng->random( 300, 1000 );
  in->encode( *hold );
  out->decode( *hold );

  EXPECT_EQ( in->col, out->col );
  EXPECT_NE( in->col, 0 );
  EXPECT_NE( out->col, 0 );
}

TEST_F( FCLayerMsgTest, ColMax ) {
  in->colMax = rng->random( 300, 1000 );
  in->encode( *hold );
  out->decode( *hold );

  EXPECT_EQ( in->colMax, out->colMax );
  EXPECT_NE( in->colMax, 0 );
  EXPECT_NE( out->colMax, 0 );
}

TEST_F( FCLayerMsgTest, RowValues ) {
  in->weight0 = rng->random( -100, 100 );
  in->weight1 = rng->random( -100, 100 );
  in->weight2 = rng->random( -100, 100 );
  in->weight3 = rng->random( -100, 100 );
  in->weight4 = rng->random( -100, 100 );
  in->bias0   = rng->random( -100, 100 );
  in->bias1   = rng->random( -100, 100 );
  in->bias2   = rng->random( -100, 100 );
  in->bias3   = rng->random( -100, 100 );
  in->bias4   = rng->random( -100, 100 );

  in->encode( *hold );
  out->decode( *hold );

  EXPECT_EQ( in->weight0, out->weight0 );
  EXPECT_EQ( in->weight1, out->weight1 );
  EXPECT_EQ( in->weight2, out->weight2 );
  EXPECT_EQ( in->weight3, out->weight3 );
  EXPECT_EQ( in->weight4, out->weight4 );

  EXPECT_EQ( in->bias0, out->bias0 );
  EXPECT_EQ( in->bias1, out->bias1 );
  EXPECT_EQ( in->bias2, out->bias2 );
  EXPECT_EQ( in->bias3, out->bias3 );
  EXPECT_EQ( in->bias4, out->bias4 );
}

#include "comms/layer_msg.h"

#include <gtest/gtest.h>

TEST( temp, EncodeDecode ) {
  LayerMsg hold;
  FCLayer in;
  FCLayer out;

  in.temp1 = 43;

  in.encode( hold );
  out.decode( hold );

  EXPECT_EQ( in.temp1, out.temp1 );
}

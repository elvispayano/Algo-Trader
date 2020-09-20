/*
  Title:
    Mock Matchers

  Description:
    This header contains a collection of the various matchers (custom equality
    evaluations) that are not needed as part of the main project. These
  functions will allow for input of custom types into mocked functions

  Author:
    Elvis Payano
*/

#ifndef MOCK_MATCHERS_H
#define MOCK_MATCHERS_H

// Utility Includes
#include "broker_types.h"
#include "matrix.h"

// Google Test Includes
#include <gmock/gmock.h>

// Matrix Equality Matcher
MATCHER_P( EqMatrix, other, "Equality matcher for Matrix" ) {
  Matrix in   = static_cast< Matrix >( arg );
  Matrix comp = static_cast< Matrix >( other );
  if ( comp.rows() != in.rows() || comp.cols() != in.cols() )
    return false;

  bool equal = true;

  for ( size_t r = 0; r < comp.rows(); ++r ) {
    for ( size_t c = 0; c < comp.cols(); ++c ) {
      equal &= ( comp( r, c ) - in( r, c ) ) < 1E-8;
    }
  }
  return equal;
};

MATCHER_P( EqOrderConfig, other, "Equality matcher for Order Config" ) {
  OrderConfig in   = static_cast< OrderConfig >( arg );
  OrderConfig comp = static_cast< OrderConfig >( other );

  if ( ( in.price == comp.price ) && ( in.quantity == comp.quantity ) &&
       ( in.purchase == comp.purchase ) && ( in.request == comp.request ) &&
       ( in.ticker == comp.ticker ) )
    return true;
  return false;
}

#endif /* MOCK_MATCHERS_H */

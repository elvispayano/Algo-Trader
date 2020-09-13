//! Stock
//!
//! The Stock class is responsible for storing all the collected (and requested)
//! data about a single stock when it is requested from the broker.
//!
//! \author   Elvis Payano
//! \date     31/08/2020
//! \version  0.0.1

// Utility Includes
#include "utilities/stock.h"

//! @fn     Stock( void )
//! @brief  Empty stock information list.
Stock::Stock( void ) {
  reset();
}

//! @fn     void reset( void )
//! @brief  Reset the class and clear any set values.
void Stock::reset( void ) {
  // Bid
  recBid = false;
  bid    = 0.0f;

  // Ask
  recAsk = false;
  ask    = 0.0f;

  // Low
  recLow = false;
  low    = 0.0f;

  // High
  recHigh = false;
  high    = 0.0f;
}

//! @fn     bool isComplete( void )
//! @brief  Check if all expected responses have been received and recorded.
bool Stock::isComplete( void ) {
  return recBid && recAsk && recLow && recHigh;
}

//! @fn     void setBid( float price)
//! @brief  Record the holding bid price reponse.
void Stock::setBid( float bid ) {
  this->bid = bid;
  recBid    = true;
}

//! @fn     void setAsk( float price )
//! @brief  Record the holding ask price.
void Stock::setAsk( float ask ) {
  this->ask = ask;
  recAsk    = true;
}

//! @fn     void  setLow( float price )
//! @brief  Record the holding low price.
void Stock::setLow( float low ) {
  this->low = low;
  recLow    = true;
}

//! @fn     void setHigh( float price )
//! @brief  Record the holding high price.
void Stock::setHigh( float high ) {
  this->high = high;
  recHigh    = true;
}

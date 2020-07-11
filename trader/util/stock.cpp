/*
  Title:
    Stock

  Description:
    This class is responsible for storing all the collected (and requested) data
    about a single stock when it is requested from the broker.

  Test:
    test_stock.cc

  Author:
    Elvis Payano
*/

// Utility Includes
#include "stock.h"

/*
  Constructor:  Stock
  Inputs:       None (void)

  Description:
    Setup default configuration for a given stock dataset
*/
Stock::Stock(void) {
  reset();
}

void Stock::reset(void) {
  // Bid
  recBid = false;
  bid = 0.0f;

  // Ask
  recAsk = false;
  ask = 0.0f;

  // Low
  recLow = false;
  low = 0.0f;

  // High
  recHigh = false;
  high = 0.0f;
}

bool Stock::isComplete(void) {
  return recBid && recAsk && recLow && recHigh;
}


void Stock::setBid(float bid) {
  this->bid = bid;
  recBid = true;
}

void Stock::setAsk(float ask) {
  this->ask = ask;
  recAsk = true;
}

void Stock::setLow(float low) {
  this->low = low;
  recLow = true;
}

void Stock::setHigh(float high) {
  this->high = high;
  recHigh = true;
}

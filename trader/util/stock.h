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

#ifndef STOCK_H
#define STOCK_H

// Utility Includes
#include "broker_types.h"

// Standard Includes
#include <string>
#include <vector>

class Stock {
public:
  Stock(void);
  ~Stock(void) {}

  // Status Functions
  void reset(void);
  bool isComplete(void);

  // Bid
  void setBid(float);
  float getBid(void) { return bid; }

  // Ask
  void setAsk(float);
  float getAsk(void) { return ask; }

  // Low
  void setLow(float);
  float getLow(void) { return low; }

  // High
  void setHigh(float);
  float getHigh(void) { return high; }

  void setAction(Requests action) { this->action = action; }
  Requests getAction(void) { return action; }

  void setTicker(std::string ticker) { this->ticker = ticker; }
  std::string getTicker(void) { return ticker; }

private:
  // Status trackers
  bool recBid, recAsk, recLow, recHigh;

  // Price trackers
  float bid, ask, low, high;

  Requests action;
  std::string ticker;
};

#endif /* STOCK_H */

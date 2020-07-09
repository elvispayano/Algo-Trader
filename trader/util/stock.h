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

private:
  // Status trackers
  bool recBid, recAsk, recLow, recHigh;

  // Price trackers
  float bid, ask, low, high;
};

#endif /* STOCK_H */

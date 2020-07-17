/*
  Title:
    Broker Types

  Description:
    A collection of various types that will be used by the trader platform to communicate with
    the broker API. These custom types allow for the trader platform to be agnostic of the API
    being utilized.

  Author:
    Elvis Payano
*/

#ifndef BROKER_TYPES_H
#define BROKER_TYPES_H

// Standard Includes
#include <string>

/*
  Enum:         Requests
  Description:
    Collection of potential requests that will be made to the broker API
*/
enum class Requests {
  UPDATE,
  MARKET,
  LIMIT,
  STOP
};

enum class ValueType {
  HIGH,
  LOW,
  OPEN,
  CLOSE,
  BID,
  ASK,
  LAST,
  VOLUME,
  NONE
};

struct OrderConfig {
  std::string ticker;
  Requests request;
  bool purchase;
  double quantity;
  double price;
  
  OrderConfig() :
    ticker(""),
    request(Requests::UPDATE),
    purchase(false),
    quantity(0.0),
    price(0.0) {}
};

#endif /* BROKER_TYPES_H */

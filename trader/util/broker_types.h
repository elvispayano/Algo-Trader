//! Broker Types
//!
//! A collection of various types that will be used by the trader platform to
//! communicate with the broker API. These custom types allow for the trader
//! platforms to be agnostic of the APIT being utilized.
//!
//! \author   Elvis Payano
//! \date     30/08/2020
//! \version  0.0.1

#ifndef BROKER_TYPES_H
#define BROKER_TYPES_H

// Standard Includes
#include <string>

//! Requests
//! Collection of potential requests that will be made to the broker API.
enum class Requests { UPDATE, MARKET, LIMIT, STOP };

//! ValueType
//! Types of responses expected from the broker API
enum class ValueType { HIGH, LOW, OPEN, CLOSE, BID, ASK, LAST, VOLUME, NONE };

//! OrderConfig
//! Message structure holding all the information required to buy or sell a
//! holding
struct OrderConfig {
  std::string ticker;    //! Holding ticker symbol
  Requests    request;   //! Type of order to create
  bool        purchase;  //! Purchase or sell holding (True=Buy; False=Sell)
  double      quantity;  //! Purchase/Sell quantity
  double      price;     //! Order price

  OrderConfig()
      : ticker( "" )
      , request( Requests::UPDATE )
      , purchase( false )
      , quantity( 0.0 )
      , price( 0.0 ) {}
};

#endif /* BROKER_TYPES_H */

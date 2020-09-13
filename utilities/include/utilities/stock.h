//! Stock
//!
//! The Stock class is responsible for storing all the collected (and requested)
//! data about a single stock when it is requested from the broker.
//!
//! \author   Elvis Payano
//! \date     31/08/2020
//! \version  0.0.1

#ifndef STOCK_H
#define STOCK_H

// Utility Includes
#include "broker_types.h"

// Standard Includes
#include <string>
#include <vector>

class Stock {
public:
  //! @fn     Stock( void )
  //! @brief  Empty stock information list.
  Stock( void );

  //! @fn     ~Stock( void )
  //! @brief  Clear any allocated memory.
  ~Stock( void ) {}

  //! @fn     void reset( void )
  //! @brief  Reset the class and clear any set values.
  void reset( void );

  //! @fn     bool isComplete( void )
  //! @brief  Check if all expected responses have been received and recorded.
  bool isComplete( void );

  //! @fn     void setBid( float price)
  //! @brief  Record the holding bid price reponse.
  void setBid( float );

  //! @fn     float getBid( void )
  //! @brief  Return the recorded holding bid price.
  float getBid( void ) { return bid; }

  //! @fn     void setAsk( float price )
  //! @brief  Record the holding ask price.
  void setAsk( float );

  //! @fn     float getAsk( void )
  //! @brief  Return the recorded holding ask price.
  float getAsk( void ) { return ask; }

  //! @fn     void  setLow( float price )
  //! @brief  Record the holding low price.
  void setLow( float );

  //! @fn     float getLow( void )
  //! @brief  Return the recorded holding low price.
  float getLow( void ) { return low; }

  //! @fn     void setHigh( float price )
  //! @brief  Record the holding high price.
  void setHigh( float );

  //! @fn     float getHigh( void )
  //! @brief  Return the recorded holding high price.
  float getHigh( void ) { return high; }

  //! @fn     void setAction( Requests action )
  //! @brief  Set the desired action that the broker should take with the
  //!         holding.
  void setAction( Requests action ) { this->action = action; }

  //! @fn     Requests getAction( void )
  //! @brief  Return the configured actions for the holding
  Requests getAction( void ) { return action; }

  //! @fn     setTicker( string ticker )
  //! @brief  Configure the holding for the specified ticker symbol
  void setTicker( std::string ticker ) { this->ticker = ticker; }

  //! @fn     getTicker( void )
  //! @brief  Return the configured holding ticker symbol
  std::string getTicker( void ) { return ticker; }

private:
  // Status trackers
  bool recBid, recAsk, recLow, recHigh;

  // Price trackers
  float bid, ask, low, high;

  Requests    action;
  std::string ticker;
};

#endif /* STOCK_H */

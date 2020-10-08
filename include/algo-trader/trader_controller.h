/// Trader Controller
///
/// The logic that controls the sequencing order in which the trader platform
/// will operate
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

#ifndef TRADER_CONTROLLER_H
#define TRADER_CONTROLLER_H

// Utility Includes
#include "utilities/fifo_bidirectional.h"

// Controller Forward Declarations
class BrokerController;
class DatabaseController;
class NetworkController;

// FIFO Forward Declarations
class BrokerResponseMsg;
class BrokerRequestMsg;

class TraderController {
public:
  TraderController( void );
  ~TraderController( void );

  void perform( void );

private:
  void initialize( void );

  BrokerController*   pBrokerCntrl;
  DatabaseController* pDatabaseCntrl;
  NetworkController*  pNetworkCntrl;

  FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* pPortBroker;
};

#endif /* TRADER_CONTROLLER_H */

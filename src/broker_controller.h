#ifndef BROKER_CONTROLLER_H
#define BROKER_CONTROLLER_H

// Comms Includes
#include "comms/broker_request_msg.h"
#include "comms/broker_request_update_msg.h"
#include "comms/broker_response_msg.h"
#include "comms/broker_response_update_msg.h"

// Utility Includes
#include "utilities/fifo_bidirectional.h"

// Forward Declarations
class BrokerBase;

class BrokerController {
public:
  BrokerController( void );
  ~BrokerController( void );

  /// @fn     void initialize( void )
  /// @brief  Initialize the broker controller with the configured settings
  void initialize( void );

  /// @fn     void perform( void )
  /// @brief  Perform a broker controller update
  void perform( void );

  /// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
  ///                       BrokerRequestMsg >* port )
  /// @param  port  Installed broker port
  /// @brief  Provide the broker interface with the installed communication
  ///         port.
  void install( FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port );

private:
  BrokerBase* pBroker;

  FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* pPort;

  BrokerRequestUpdateMsg bReqUpdateMsg;
};

#endif /* BROKER_CONTROLLER_H */

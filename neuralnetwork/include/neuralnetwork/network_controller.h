/// Neural Network Controller
///
/// The neural network controller interface that handles the platforms with the
/// various neural networks that are deployed
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

// Neural Network Includes
#include "neural_network.h"

// Comms Includes
#include "comms/broker_request_msg.h"
#include "comms/broker_request_update_msg.h"
#include "comms/broker_response_msg.h"
#include "comms/broker_response_update_msg.h"
#include "comms/layer_msg.h"

// Utility Includes
#include "utilities/fifo_bidirectional.h"

// Standard Includes
#include <map>
#include <vector>

// Forward Declaration
class NeuralNetwork;

class NetworkController {
public:
  NetworkController( void );
  ~NetworkController( void );

  void perform( void );

  /// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
  ///                       BrokerRequestMsg >* port )
  /// @param  port  Installed broker port
  /// @brief  Provide the broker interface with the installed communication
  ///         port.
  void install( FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port );

private:
  void processInputs( void );
  void update( void );
  void processOutputs( void );

  /// @fn     void processBrokerInputs( void )
  /// @brief  Process responses from broker API
  void processBrokerInputs( void );

  /// @fn     void updateNetworkInputs( BrokerResponseUpdateMsg msg )
  /// @param  msg   Formatted broker response message
  /// @brief  Update neural network inputs
  void updateNetworkInputs( BrokerResponseUpdateMsg msg );

  std::map<std::string, NeuralNetwork*> networkList;
  std::map<std::string, Matrix>         networkInputs;

  // Port Definitions
  FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* pBrokerPort;

  BrokerResponseMsg       brokerResponse;
  BrokerResponseUpdateMsg brokerResponseUpdate;

  LayerMsg* LayerInputMsg;
};

#endif /* NETWORK_CONTROLLER_H */

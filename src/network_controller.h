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
#include "neuralnetwork/neural_network.h"

// Comms Includes
#include "comms/broker_request_msg.h"
#include "comms/broker_request_update_msg.h"
#include "comms/broker_response_msg.h"
#include "comms/broker_response_update_msg.h"
#include "comms/fc_layer_msg.h"
#include "comms/layer_msg.h"

// Utility Includes
#include "utilities/fifo_bidirectional.h"
#include "utilities/fifo_unidirectional.h"

// Standard Includes
#include <map>
#include <vector>

// Forward Declaration
class DataServer;
class NeuralNetwork;

class NetworkController {
public:
  NetworkController( DataServer* server );
  ~NetworkController( void );

  void perform( void );

  /// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
  ///                       BrokerRequestMsg >* port )
  /// @param  port  Installed broker port
  /// @brief  Provide the broker interface with the installed communication
  ///         port.
  void install( FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port );

  /// @fn     void install( FIFOBidirectional<LayerMsg, LayerMsg>* port )
  /// @param  port  Installed database port
  /// @brief  Provide the database interface with the installed communication
  ///         port.
  void install( FIFOBidirectional<LayerMsg, LayerMsg>* port );

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

  /// @fn     void processDatabaseInputs( void )
  /// @brief  Process responses from the database
  void processDatabaseInputs( void );

  /// @fn     void configure( FCLayer )
  /// @brief  Reconfigure selected network
  void reconfigure( FCLayer msg );

  /// @fn     load( void )
  /// @breif  Create a new network used within the system
  void load( void );

  /// @fn     configure( void )
  /// @brief  Configure the loaded neural networks
  void configure( void );

  std::map<std::string, NeuralNetwork*> networkList;
  std::map<std::string, Matrix>         networkInputs;

  // Port Definitions
  FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* pBrokerPort;
  FIFOBidirectional<LayerMsg, LayerMsg>*                  pDatabasePort;

  BrokerResponseUpdateMsg brokerResponseUpdate;

  FCLayer databaseResponseFC;

  DataServer* pServer;
};

#endif /* NETWORK_CONTROLLER_H */

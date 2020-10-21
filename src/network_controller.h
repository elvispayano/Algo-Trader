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
#include "comms/database_request_layer_msg.h"
#include "comms/database_request_msg.h"
#include "comms/database_response_layer_msg.h"
#include "comms/database_response_msg.h"
#include "comms/database_response_network_msg.h"
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

  /// @fn     void install( FIFOBidirectional<DatabaseResponseMsg,
  ///                       DatabaseRequestMsg>* port )
  /// @param  port  Installed database port
  /// @brief  Provide the database interface with the installed communication
  ///         port.
  void
  install( FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>* port );

private:
  /// @fn     void processInputs( void )
  /// @brief  Process broker and database inputs
  void processInputs( void );

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

  /// @fn     void updateNetworks( DatabaseResponseNetworkMsg msg )
  /// @param  msg   Input message
  /// @brief  Update the networks being used
  void updateLoadedNetworks( DatabaseResponseNetworkMsg& msg );

  /// @fn     void configureNetwork( DatabaseResponseLayerMsg msg )
  /// @param  msg   Input message
  /// @brief  Create network layers
  void configureNetwork( DatabaseResponseLayerMsg msg );

  void update( void );

  /// @fn     void processOutputs( void )
  /// @brief  Process broker and database requests
  void processOutputs( void );

  void processDatabaseOutputs( void );

  void requestConfiguration( std::string ticker, unsigned int layerNum );

  void writeMessage( DatabaseRequestMsg msg );

  typedef std::map<std::string, NeuralNetwork*> NetworkMap;

  std::map<std::string, Matrix>         networkInputs;

  // Port Definitions
  FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>*     pBrokerPort;
  FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>* pDatabasePort;

  // Broker Response Messages
  BrokerResponseUpdateMsg brokerResponseUpdate;

  // Database Response Messages
  DatabaseRequestMsg         databaseRequest;
  DatabaseResponseNetworkMsg databaseResponseNetwork;
  DatabaseResponseLayerMsg   databaseResponseLayer;

  FCLayer databaseResponseFC;

  DataServer* pServer;
};

#endif /* NETWORK_CONTROLLER_H */

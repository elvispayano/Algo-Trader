/// Neural Network Controller
///
/// The neural network controller interface that handles the platforms with the
/// various neural networks that are deployed
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

// Algo-Trader Includes
#include "network_controller.h"
#include "data_server.h"

// Neural Network Includes
#include "neuralnetwork/neural_network.h"

NetworkController::NetworkController( DataServer* server )
    : pServer( server ) {
  pBrokerPort   = 0;
  pDatabasePort = 0;
}

NetworkController::~NetworkController( void ) {}

/// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
///                       BrokerRequestMsg >* port )
/// @param  port  Installed broker port
/// @brief  Provide the broker interface with the installed communication
///         port.
void NetworkController::install(
    FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port ) {
  pBrokerPort = port;
}

/// @fn     void install( FIFOBidirectional<DatabaseResponseMsg,
///                       DatabaseRequestMsg>* port
/// )
/// @param  port  Installed database port
/// @brief  Provide the database interface with the installed communication
///         port.
void NetworkController::install(
    FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>* port ) {
  pDatabasePort = port;
}

void NetworkController::perform( void ) {
  processInputs();

  update();

  processOutputs();
}

void NetworkController::processInputs( void ) {
  // Processing Broker Inputs
  processBrokerInputs();

  // Processing Database Inputs
  processDatabaseInputs();
}

void NetworkController::update( void ) {
  NeuralNetwork* network;
  Matrix         input;

  NetworkMap networkList = pServer->getNetworkList();
  for ( auto& iter : networkList ) {
    std::string ticker = iter.first;
    network            = iter.second;

    if ( networkInputs.find( ticker ) == networkInputs.end() ) {
      continue;
    }
    input.set( networkInputs[ticker] );
    networkInputs.erase( ticker );

    Matrix output = network->process( input );
  }
}

void NetworkController::processOutputs( void ) {
  BrokerRequestUpdateMsg requestUpdateMsg;
  BrokerRequestMsg       requestMsg;

  NetworkMap& networkList = pServer->getNetworkList();
  for ( auto iter : networkList ) {
    if ( !iter.second->checkConfiguration() ) {
      continue;
    }

    std::string  ticker = iter.first;
    unsigned int len    = ticker.size();

    requestUpdateMsg.s1 = ( len > 0 ) ? ticker.c_str()[0] : '\0';
    requestUpdateMsg.s2 = ( len > 0 ) ? ticker.c_str()[1] : '\0';
    requestUpdateMsg.s3 = ( len > 1 ) ? ticker.c_str()[2] : '\0';
    requestUpdateMsg.s4 = ( len > 2 ) ? ticker.c_str()[3] : '\0';
    requestUpdateMsg.s5 = ( len > 3 ) ? ticker.c_str()[4] : '\0';
    requestUpdateMsg.s6 = ( len > 4 ) ? ticker.c_str()[5] : '\0';

    if ( requestUpdateMsg.encode( &requestMsg ) ) {
      pBrokerPort->putOutput( requestMsg );
    }
  }

  // Processing Database Outputs
  processDatabaseOutputs();
}

/// @fn     void processBrokerInputs( void )
/// @brief  Process responses from broker API
void NetworkController::processBrokerInputs( void ) {
  BrokerResponseMsg brokerResponse;
  if ( !pBrokerPort->getInput( brokerResponse ) ) {
    return;
  }

  switch ( brokerResponse.getID() ) {
  case ResponseID::UPDATE:
    if ( brokerResponseUpdate.decode( &brokerResponse ) ) {
      updateNetworkInputs( brokerResponseUpdate );
    }
  }
}

/// @fn     void updateNetworkInputs( BrokerResponseUpdateMsg msg )
/// @param  msg   Formatted broker response message
/// @brief  Update neural network inputs
void NetworkController::updateNetworkInputs( BrokerResponseUpdateMsg msg ) {
  std::string ticker;
  ticker.push_back( msg.s1 );
  ticker.push_back( msg.s2 );
  ticker.push_back( msg.s3 );
  ticker.push_back( msg.s4 );
  ticker.push_back( msg.s5 );
  ticker.push_back( msg.s6 );
  for ( unsigned int i = 0; i < ticker.size(); ++i ) {
    if ( ticker.back() == '\0' )
      ticker.pop_back();
  }

  Matrix input( 5, 1, 0.0 );
  input( 0, 0 ) = msg.ask;
  input( 1, 0 ) = msg.bid;
  input( 2, 0 ) = msg.high;
  input( 3, 0 ) = msg.low;
  input( 4, 0 ) = msg.last;

  networkInputs[ticker].set( input );
}

/// @fn     void processDatabaseInputs( void )
/// @brief  Process responses from the database
void NetworkController::processDatabaseInputs( void ) {
  DatabaseResponseMsg response;
  if ( !pDatabasePort->getInput( response ) ) {
    return;
  }

  switch ( response.getID() ) {
  case DatabaseResponseID::NETWORK:
    if ( databaseResponseNetwork.decode( &response ) ) {
      updateLoadedNetworks( databaseResponseNetwork );
    }
    break;

  case DatabaseResponseID::LAYER:
    if ( databaseResponseLayer.decode( &response ) ) {
      configureNetwork( databaseResponseLayer );
    }
    break;

  default: /* DatabaseResponseID::UNKNOWN */
    printf( "Error: Unknown Database Response\n" );
  }
}

/// @fn     void updateNetworks( DatabaseResponseNetworkMsg msg )
/// @param  msg   Input message
/// @brief  Update the networks being used
void NetworkController::updateLoadedNetworks(
    DatabaseResponseNetworkMsg& msg ) {

  NetworkMap& networkList = pServer->getNetworkList();
  switch ( msg.action ) {
  case DbNetworkID::ADD:
    networkList[msg.ticker] = new NeuralNetwork( msg.ticker, msg.layerCount );
    printf( "NetworkCtrl: Added new Network: %s\n", msg.ticker.c_str() );
    break;

  case DbNetworkID::REMOVE:
    if ( networkList[msg.ticker] ) {
      delete networkList[msg.ticker];
      networkList.erase( networkList.find( msg.ticker ) );
      printf( "NetworkCtrl: Removed Network: %s\n", msg.ticker.c_str() );
    }
    break;

  default: /* DbNetworkID::UNKNOWN */
    printf( "Error: Unknown Network Action\n" );
  }
}

/// @fn     void configureNetwork( DatabaseResponseLayerMsg msg )
/// @param  msg   Input message
/// @brief  Create network layers
void NetworkController::configureNetwork( DatabaseResponseLayerMsg msg ) {
  NetworkMap& networkList = pServer->getNetworkList();
  if ( networkList.find( msg.ticker ) == networkList.end() ) {
    return;
  }

  networkList[msg.ticker]->addLayer(
      msg.layer, msg.activation, msg.numberOfInputs, msg.numberOfNodes );
}

void NetworkController::processDatabaseOutputs( void ) {
  NetworkMap networkList = pServer->getNetworkList();

  for ( auto network : networkList ) {
    if ( !network.second->layersAdded() ) {
      requestConfiguration( network.first,
                            network.second->getLayerCount() + 1 );
      break;
    }
  }
}

void NetworkController::requestConfiguration( std::string  ticker,
                                              unsigned int layerNum ) {
  DatabaseRequestLayerMsg msg;
  msg.ticker      = ticker;
  msg.layerNumber = layerNum;
  if ( msg.encode( &databaseRequest ) ) {
    writeMessage( databaseRequest );
  }
}

void NetworkController::writeMessage( DatabaseRequestMsg msg ) {
  if ( !pDatabasePort->putOutput( msg ) ) {
    printf( "NetworkCntl: Error Writing To Database Bus\n" );
  }
}

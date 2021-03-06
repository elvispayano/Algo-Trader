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
#include "neuralnetwork/layer_base.h"
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

    requestUpdateMsg.ticker = iter.first;
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
  Matrix input( 5, 1, 0.0 );
  input( 0, 0 ) = msg.ask;
  input( 1, 0 ) = msg.bid;
  input( 2, 0 ) = msg.high;
  input( 3, 0 ) = msg.low;
  input( 4, 0 ) = msg.last;

  networkInputs[msg.ticker].set( input );
}

/// @fn     void processDatabaseInputs( void )
/// @brief  Process responses from the database
void NetworkController::processDatabaseInputs( void ) {
  DatabaseResponseMsg response;
  while ( pDatabasePort->getInput( response ) ) {
    switch ( response.getID() ) {
    case DatabaseResponseID::NETWORK:
      if ( databaseResponseNetwork.decode( &response ) ) {
        updateLoadedNetworks();
      }
      break;

    case DatabaseResponseID::LAYER:
      if ( databaseResponseLayer.decode( &response ) ) {
        configureNetwork();
      }
      break;

    case DatabaseResponseID::HYPERPARAM:
      if ( databaseResponseHyperparam.decode( &response ) ) {
        configureLayer();
      }
      break;

    default: /* DatabaseResponseID::UNKNOWN */
      printf( "Error: Unknown Database Response\n" );
    }
  }
}

/// @fn     void updateNetworks( void )
/// @brief  Update the networks being used
void NetworkController::updateLoadedNetworks( void ) {

  NetworkMap&  networkList = pServer->getNetworkList();
  std::string  ticker      = databaseResponseNetwork.ticker;
  unsigned int layerCount  = databaseResponseNetwork.layerCount;
  switch ( databaseResponseNetwork.action ) {
  case DbNetworkID::ADD:
    networkList[ticker] = new NeuralNetwork( ticker, layerCount );
    printf( "NetworkCtrl: Added new Network: %s\n", ticker.c_str() );
    break;

  case DbNetworkID::REMOVE:
    if ( networkList[ticker] ) {
      delete networkList[ticker];
      networkList.erase( networkList.find( ticker ) );
      printf( "NetworkCtrl: Removed Network: %s\n", ticker.c_str() );
    }
    break;

  default: /* DbNetworkID::UNKNOWN */
    printf( "Error: Unknown Network Action\n" );
  }
}

/// @fn     void configureNetwork( void )
/// @brief  Create network layers
void NetworkController::configureNetwork( void ) {
  NetworkMap& networkList = pServer->getNetworkList();
  if ( networkList.find( databaseResponseLayer.ticker ) == networkList.end() ) {
    return;
  }

  networkList[databaseResponseLayer.ticker]->addLayer(
      databaseResponseLayer.layer,
      databaseResponseLayer.activation,
      databaseResponseLayer.numberOfInputs,
      databaseResponseLayer.numberOfNodes );
}

void NetworkController::configureLayer( void ) {
  std::string ticker = databaseResponseHyperparam.ticker;
  unsigned int layerNum = databaseResponseHyperparam.layerNum;
  unsigned int index    = databaseResponseHyperparam.index;
  float        value    = databaseResponseHyperparam.value;

  NetworkMap& networkList = pServer->getNetworkList();
  networkList[ticker]->getLayerList()[layerNum-1]->configure( index, value );
}

void NetworkController::processDatabaseOutputs( void ) {
  DatabaseRequestLayerMsg msg;
  NetworkMap              networkList = pServer->getNetworkList();

  for ( auto network : networkList ) {
    // Request Next Layer
    if ( !network.second->layersAdded() ) {
      requestConfiguration( network.first,
                            network.second->getLayerCount() + 1 );
    }

    // Request Layer Hyperparam
    unsigned int layerNum = 1;
    for ( auto layer : network.second->getLayerList() ) {
      if ( !layer->isConfigured() ) {
        DatabaseRequestHyperparamMsg request;
        request.ticker   = network.first;
        request.index    = layer->nextIndex();
        request.layerNum = layerNum;
        if ( request.encode( &msg ) ) {
          writeMessage( msg );
        }
      }
      ++layerNum;
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

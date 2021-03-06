/*
  Title:
    Interfaces Mock Classes

  Description:
    This header contains a collection of the various mocks of classes
    within the Interfaces library for use throughout tests

  Author:
    Elvis Payano
*/

#ifndef MOCK_INTERFACES_H
#define MOCK_INTERFACES_H

// Interface Includes
#include "interfaces/broker_base.h"
#include "interfaces/database_base.h"
#include "interfaces/ib_wrapper.h"

// Utility Includes
#include "utilities/broker_types.h"
#include "utilities/stock.h"

// Google Mock Includes
#include <gmock/gmock.h>

// Standard Includes
#include <string>

// Mocked Database Base
class MockDatabaseBase : public DatabaseBase {
public:
  MOCK_METHOD0( connect, bool( void ) );
  MOCK_METHOD0( disconnect, void( void ) );
  MOCK_METHOD0( getNetworkCount, int( void ) );
  MOCK_METHOD1( getNetwork, std::string( size_t ) );
  MOCK_METHOD1( getLayerCount, int( std::string ) );
  MOCK_METHOD2( getLayer, LayerConfiguration( std::string, unsigned int ) );
};

// Mocked Broker Base
class MockBrokerBase : public BrokerBase {
public:
  MOCK_METHOD0( connectionManager, void( void ) );
  MOCK_METHOD0( terminateConnection, void( void ) );
  MOCK_METHOD1( responseReady, bool( std::string ) );
  MOCK_METHOD1( getResponse, Stock( std::string ) );
  MOCK_METHOD1( addToQueue, void( OrderConfig ) );
};

// Mocked Interactive Broker Wrapper
class MockedIBWrapper : public IBWrapper {
public:
  MockedIBWrapper( std::string host, int port, int clientID )
      : IBWrapper( host, port, clientID ) {}
  MOCK_METHOD0( connect, bool( void ) );
  MOCK_METHOD0( disconnect, void( void ) );
  MOCK_METHOD1( getCurrentPrice, void( std::string ) );
  MOCK_METHOD3( orderMarket, void( std::string, std::string, double ) );
  MOCK_METHOD4( orderLimit, void( std::string, std::string, double, double ) );
  MOCK_METHOD4( orderStop, void( std::string, std::string, double, double ) );
  MOCK_METHOD0( processMessages, void( void ) );
  MOCK_METHOD0( responseReady, bool( void ) );
  MOCK_METHOD0( getResponse, Stock( void ) );
};

#endif /* MOCK_INTERFACES_H */

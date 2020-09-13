// Interface Includes
#include "interfaces/ib_wrapper.h"

// Google Mock Includes
#include <gmock/gmock.h>

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

#ifndef MOCK_DATABASE_BASE_H
#define MOCK_DATABASE_BASE_H
// Interface Includes
#include "interfaces/database_base.h"

// Google Mock Includes
#include <gmock/gmock.h>

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

#endif /* MOCK_DATABASE_BASE_H */

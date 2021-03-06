/*
  Title:
    Postgres

  Description:
    This class is responsible for configuring and managing the PostgreSQL
    database connection. The main objective of this class is to ensure that
    a requests are properly fulfilled

  Author:
    Elvis Payano
*/

// Interface Includes
#include "postgres.h"

// Postgres (External) Includes
#include <libpq-fe.h>

// Standard Includes
#include <cstring>

/*
  Constructor:  Postgres
  Inputs:       host, port, opt, tty, database, username, password (all char*)

  Description:
    Setup configuration for postgres database connection
*/
Postgres::Postgres( char* host,
                    char* port,
                    char* opt,
                    char* tty,
                    char* db,
                    char* user,
                    char* pass )
    : host( host )
    , port( port )
    , opt( opt )
    , tty( tty )
    , db( db )
    , user( user )
    , pass( pass ) {
  connection = nullptr;
  results    = nullptr;
  clearQuery();
}

/*
  Destructor:   ~Postgres
  Inputs:       None (void)

  Description:
    Ensure postgres connection is safely terminated during object
    destruction
*/
Postgres::~Postgres( void ) {
  disconnect();
}

/// @fn     bool isConnected( void )
/// @brief  Check the connection status to the database
bool Postgres::isConnected( void ) {
  return PQstatus( connection ) == ConnStatusType::CONNECTION_OK;
}

/// @fn     void connect( void )
/// @brief  Attempt to establish a database connection using the configured
///         parameters
void Postgres::connect( void ) {
  // Attemp connection
  connection = PQsetdbLogin( host.c_str(),
                             port.c_str(),
                             opt.c_str(),
                             tty.c_str(),
                             db.c_str(),
                             user.c_str(),
                             pass.c_str() );
}

/// @fn     void disconnect( void )
/// @brief  Terminate the established connection to the database
void Postgres::disconnect( void ) {
  if ( isConnected() )
    PQfinish( connection );
}

/*
  Function:     clearQuery
  Inputs:       None (void)

  Description:
    Clear query buffer of any
*/
void Postgres::clearQuery( void ) {
  memset( queryBuffer, '\0', 100 );
}

/*
  Function:     exec
  Inputs:       query (string)
  Outputs:      resultValue (char*)

  Description:
    Execute the provided query
*/
char* Postgres::exec( std::string query ) {
  // Prevent function usage if connection is not established
  if ( PQstatus( connection ) != ConnStatusType::CONNECTION_OK )
    return NULL;
  results = PQexec( connection, query.c_str() );
  return PQgetvalue( results, 0, 0 );
}

/*
  Function:     execFunc
  Inputs:       func (string)
  Outputs:      result (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func()"
    where func is the provided database function
*/
char* Postgres::execFunc( std::string func ) {
  clearQuery();
  sprintf( queryBuffer, "SELECT * FROM %s()", func.c_str() );
  return exec( queryBuffer );
}

/*
  Function:     execFunc
  Inputs:       func (char*), id (int)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id)"
    where func is the provided database function and id is the function input
*/
char* Postgres::execFunc( std::string func, int id ) {
  clearQuery();
  sprintf( queryBuffer, "SELECT * FROM %s(%d)", func.c_str(), id );
  return exec( queryBuffer );
}

/*
  Function:     execFunc
  Inputs:       func (string), ticker (char*)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id)"
    where func is the provided database function and id is the function input
*/
char* Postgres::execFunc( std::string func, std::string ticker ) {
  clearQuery();
  sprintf(
      queryBuffer, "SELECT * FROM %s('%s')", func.c_str(), ticker.c_str() );
  return exec( queryBuffer );
}

/*
  Function:     execFunc
  Inputs:       func (string), ticker (string), num (int)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id, num)"
    where func is the provided database function and id & num are the function
  inputs
*/
char* Postgres::execFunc( std::string func, std::string ticker, int num ) {
  clearQuery();
  sprintf( queryBuffer,
           "SELECT * FROM %s('%s', %d)",
           func.c_str(),
           ticker.c_str(),
           num );
  return exec( queryBuffer );
}

char* Postgres::execFunc( std::string func, std::string ticker, int num1, int num2) {
  clearQuery();
  sprintf( queryBuffer,
           "SELECT * FROM %s('%s', %d, %d)",
           func.c_str(),
           ticker.c_str(),
           num1, num2 );
  return exec( queryBuffer );
}

/*
  Function:     getNetworkCount
  Inputs:       None (void)
  Output:       count (int)

  Description:
    Obtain the total count of networks in the database
*/
int Postgres::getNetworkCount( void ) {
  // Database response
  std::string valueStr = execFunc( "network_count" );
  return toInt( valueStr.c_str() );
}

/*
  Function:     getNetwork
  Inputs:       id (size_t)
  Outputs:      ticker (char*)

  Description:
    Obtain the ticker symbol associated with the provided id
*/
std::string Postgres::getNetwork( size_t id ) {
  if ( ( id < 1 ) || ( id > getNetworkCount() ) )
    return NULL;
  return execFunc( "get_network", id );
}

/*
  Function:     layerCount
  Inputs:       ticker (string)
  Outputs:      count (int)

  Description:
    Obtain the expected layer count for each neural network in the database
*/
int Postgres::getLayerCount( std::string ticker ) {
  std::string valueStr = execFunc( "layer_count", ticker.c_str() );
  return toInt( valueStr );
}

/*
  Function:     getInputs
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request specifying how many inputs are present for the layer
*/
int Postgres::getInputs( std::string ticker, int layerNum ) {
  std::string valueStr = execFunc( "layer_inputs", ticker.c_str(), layerNum );
  return toInt( valueStr );
}

/*
  Function:     getNodes
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request specifying how many nodes are present for the layer
*/
int Postgres::getNodes( std::string ticker, int layerNum ) {
  std::string valueStr = execFunc( "layer_nodes", ticker.c_str(), layerNum );
  return toInt( valueStr );
}

/*
  Function:     getIndex
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request for specific layer index to mark when to search for
    weight and bias values within the database
*/
int Postgres::getIndex( std::string ticker, int layerNum ) {
  std::string valueStr = execFunc( "layer_ind", ticker.c_str(), layerNum );
  return toInt( valueStr );
}

/*
  Function:     getActivation
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request for specific layer activation function type
*/
ActivationTypes Postgres::getActivation( std::string ticker, int layerNum ) {
  std::string valueStr =
      execFunc( "layer_activation", ticker.c_str(), layerNum );
  int value = toInt( valueStr );
  if ( value >= static_cast<int>( ActivationTypes::UNKNOWN ) ||
       valueStr.empty() )
    return ActivationTypes::UNKNOWN;
  return static_cast<ActivationTypes>( value );
}

/*
  Function:     getLayerType
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request for specific layer type
*/
LayerTypes Postgres::getLayerType( std::string ticker, int layerNum ) {
  std::string valueStr = execFunc( "layer_type", ticker.c_str(), layerNum );
  int         value    = toInt( valueStr );
  if ( value >= static_cast<int>( LayerTypes::UNKNOWN ) || valueStr.empty() )
    return LayerTypes::UNKNOWN;
  return static_cast<LayerTypes>( value );
}

float Postgres::getHyperparam( std::string  ticker,
  unsigned int layerNum,
  unsigned int index) {
  std::string valueStr = execFunc( "get_hyperparam", ticker.c_str(), index, layerNum );
  return toFloat( valueStr );
}

/*
  Function:     getWeightBias
  Inputs:       ticker (string), index (int)

  Description:
    SQL request for weight and bias values
*/
double Postgres::getWeightBias( std::string ticker, int index ) {
  std::string valueStr = execFunc( "get_wb", ticker.c_str(), index );
  return toFloat( valueStr );
}

/*
  Function:     getLayer
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request for all configurations parameters for a specified layer within
  the requested network.
*/
LayerConfiguration Postgres::getLayer( std::string  ticker,
                                       unsigned int layerNum ) {
  LayerConfiguration layer;
  layer.activation = getActivation( ticker, layerNum );
  layer.layer      = getLayerType( ticker, layerNum );

  layer.nodes = getNodes( ticker, layerNum );
  // layer.inputs  = getInputs( ticker, layerNum );
  // layer.weight.resize( layer.nodes, layer.inputs, 0.0 );
  // layer.bias.resize( layer.nodes, 1, 0.0 );

  int index = getIndex( ticker, layerNum );
  // for ( size_t col = 0; col < layer.inputs; ++col ) {
  //  for ( size_t row = 0; row < layer.nodes; ++row ) {
  //    layer.weight( row, col ) = getWeightBias( ticker, index++ );
  //  }
  //}
  // for ( size_t row = 0; row < layer.nodes; ++row )
  // layer.bias( row, 0 ) = getWeightBias( ticker, index++ );

  return layer;
}

/// @fn     std::string getNextNetwork( void )
/// @brief  Get the next available network that will be loaded
std::string Postgres::getNextNetwork(void) {
  static unsigned int networksLoaded = 0;
  return getNetwork( ++networksLoaded );
}

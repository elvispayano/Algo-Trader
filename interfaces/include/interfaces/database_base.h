/*
  Title:
    Database Base

  Description:
    This class is the template configuration for managing connections to
    external Databases. This base implementation will allow for the selected
    solution to be independent of how the project is designed.

  Test:
    test_database_base.cc

  Author:
    Elvis Payano
*/

#ifndef DATABASE_BASE_H
#define DATABASE_BASE_H

// Standard Includes
#include <string>

// Utilities Includes
#include "utilities/network_types.h"

class DatabaseBase {
public:
  // Constructor
  DatabaseBase( void ){};

  // Destructor
  ~DatabaseBase( void ){};

  /// @fn     bool isConnected( void )
  /// @brief  Check the connection status to the database
  virtual bool isConnected( void ) = 0;

  /// @fn     void connect( void )
  /// @brief  Attempt to establish a database connection using the configured
  ///         parameters
  virtual void connect( void ) = 0;

  /// @fn     void disconnect( void )
  /// @brief  Terminate the established connection to the database
  virtual void disconnect( void ) = 0;

  /// @fn     void performInput( void )
  /// @brief  Process all received inputs received from database
  virtual void performInput( void ) = 0;

  /// @fn     void performOutput( void )
  /// @brief  Send all outgoing messages to database
  virtual void performOutput( void ) = 0;

  // Network configuration
  virtual int         getNetworkCount( void )             = 0;
  virtual std::string getNetwork( size_t id )             = 0;
  virtual int         getLayerCount( std::string ticker ) = 0;

  // Layer configuration
  virtual LayerConfiguration getLayer( std::string  ticker,
                                       unsigned int layerNum ) = 0;

  // Support functions
  int   toInt( std::string in );
  float toFloat( std::string in );
};

#endif /* DATABASE_BASE_H */

/// Data Server
///
/// An internal data server class that will retain all common information that
/// will be accessed across various subsystems
///
/// \author   Elvis Payano
/// \date     11/10/2020
/// \version  0.0.1

#ifndef DATA_SERVER_H
#define DATA_SERVER_H

// Standard Includes
#include <map>
#include <string>

// Forward Declarations
class NeuralNetwork;

class DataServer {
public:
  typedef std::map<std::string, NeuralNetwork*> NetworkMap;

  DataServer( void );
  ~DataServer( void ) {}

  void initialize( void );

  void addNetwork( std::string name );
  bool getNetwork( std::string& name );

  NetworkMap&  getNetworkList( void ) { return networkList; }

private:
  NetworkMap networkList;
};

#endif /* DATA_SERVER_H */

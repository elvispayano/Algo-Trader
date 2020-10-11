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
#include <string>
#include <vector>

class DataServer {
public:
  DataServer( void );
  ~DataServer( void ) {}

  void initialize( void );

  void addNetwork( std::string network ) { networkList.push_back( network ); }

  unsigned int getNumberNetworksLoaded( void ) { return numberNetworksLoaded; }

  void setNumberNetworksLoaded( unsigned int num ) {
    numberNetworksLoaded = num;
  }

private:
  unsigned int numberNetworksLoaded;

  std::vector<std::string> networkList;
};

#endif /* DATA_SERVER_H */

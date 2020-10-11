/// Data Server
///
/// An internal data server class that will retain all common information that
/// will be accessed across various subsystems
///
/// \author   Elvis Payano
/// \date     11/10/2020
/// \version  0.0.1

#include "data_server.h"

DataServer::DataServer( void ) {
  initialize();
}

void DataServer::initialize( void ) {
  numberNetworksLoaded = 0;
}

std::string DataServer::getNetwork(void) {
  std::string ticker;
  if (networkList.size() == 0) {
    return ticker;
  }
  ticker = networkList.back();
  networkList.pop_back();
  return ticker;
}

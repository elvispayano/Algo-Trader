#include <iostream>
#include <stdio.h>

#include "interfaces/ib_wrapper.h"
#include "interfaces/interactive_broker.h"

InteractiveBroker* broker;

void buy( void ) {
  OrderConfig order;
  order.request  = Requests::LIMIT;
  order.purchase = true;

  printf( "Ticker: " );
  std::cin >> order.ticker;

  printf( "Purchase Price: " );
  std::cin >> order.price;

  printf( "Quantity: " );
  std::cin >> order.quantity;
  broker->addToQueue( order );
}

void sell( void ) {
  OrderConfig order;
  order.request = Requests::LIMIT;

  printf( "Ticker: " );
  std::cin >> order.ticker;

  printf( "Purchase Price: " );
  std::cin >> order.price;

  printf( "Quantity: " );
  std::cin >> order.quantity;
  broker->addToQueue( order );
}

bool runInterface( void ) {
  int selection;

  printf( "Buy: 1\nSell: 2\nHold: 3\nExit: 0\n" );
  std::cin >> selection;
  switch ( selection ) {
  case 1:
    buy();
    break;
  case 2:
    sell();
    break;
  }
  return ( selection != 0 );
}

int main( void ) {
  IBWrapper* wrapper = new IBWrapper( "127.0.0.1", 6550, 0 );
  broker             = new InteractiveBroker( wrapper );
  broker->connectionManager();

  while ( runInterface() ) {}

  delete broker;
  return 0;
}

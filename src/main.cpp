#include <csignal>
#include <iostream>
#include <Windows.h>

#include "algo-trader/trader_controller.h"

bool logic;
TraderController trader;

void killswitch( int signum ) {
  printf( "Terminating Session\n");
  logic = false;
}

int main() {
  // register signal SIGINT and signal handler
  signal( SIGINT, killswitch );
  logic = true;
  while ( logic ) {
    trader.perform();
    Sleep( 1000 );
  }

  return 0;
}
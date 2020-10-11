#include <csignal>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "trader_controller.h"

bool             logic;
TraderController trader;

void killswitch( int signum ) {
  printf( "Terminating Session\n" );
  logic = false;
}

int main() {
  // register signal SIGINT and signal handler
  signal( SIGINT, killswitch );
  logic = true;
  while ( logic ) {
    trader.perform();
#ifdef _WIN32
    Sleep( 1000 );
#else
    sleep( 1000 );
#endif
  }

  return 0;
}

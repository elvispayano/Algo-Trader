/*
  Title:
    PG Network

  Description:
    This class is responsible for housing all functionality with the
    network table within the postgres database. Additionally, it
    will configure output and return with expected types.

  Tests:
    test_pg_network.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_network.h"

// Standard Includes
#include <stdlib.h>

/*
  Constructor:  PGNetwork
  Inputs:       None (void)

  Description:
    Set table settings

*/
PGNetwork::PGNetwork(void) {
  table = "network";
}

/*
  Destructor:   ~PGNetwork
  Inputs:       None (void)

  Description:
    Default destructor

*/
PGNetwork::~PGNetwork(void) {

}

/*
  Function:     networkCount
  Inputs:       None (void)
  Output:       count (int)

  Description:
    Obtain the total count of networks in the database
*/
int PGNetwork::networkCount(void) {
  // Database response
  char* valueStr = execFunc("network_count");

  // Convert to integer
  int value = atoi(valueStr);
  return value;
}

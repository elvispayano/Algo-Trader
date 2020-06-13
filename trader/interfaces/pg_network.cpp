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
  table = "networks";
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

  // Null check
  if (!valueStr) return 0;

  // Convert to integer
  int value = atoi(valueStr);
  return value;
}
/*
  Function:     getNetwork
  Inputs:       id (int)
  Outputs:      ticker (char*)

  Description:
    Obtain the ticker symbol associated with the provided id
*/
char* PGNetwork::getNetwork(int id) {
  if ((id < 1) || (id >= networkCount())) return NULL;
  return execFunc("get_network", id);
}

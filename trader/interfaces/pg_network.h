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

#ifndef PG_NETWORK_H
#define PG_NETWORK_H

// Interface Includes
#include "pg_connect.h"

class PGNetwork : public PGConnect {
public:
  // Constructor
  PGNetwork(void);

  // Destructor
  ~PGNetwork(void);

  // Network SQL Interface
  int networkCount(void);
};

#endif /* PG_NETWORK_H */
/*
  Title:
    PG Network

  Description:
    This class is responsible for housing all functionality layers table
    within the postgres databse. Additionally, it will configure outputs
    and return with expected types.

  Tests:
    test_pg_layer.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_connect.h"

class PGLayer : public PGConnect {
public:
  // Constructor
  PGLayer(void);

  // Destructor
  ~PGLayer(void);
};
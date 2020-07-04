/*
  Title:
    Postgres

  Description:
    This class is responsible for configuring and managing the PostgreSQL
    database connection. The main objective of this class is to ensure that
    a requests are properly fulfilled

  Author:
    Elvis Payano
*/

// Interface Includes
#include "postgres.h"

// Postgres (External) Includes
#include <libpq-fe.h>

/*
  Constructor:  Postgres
  Inputs:       host, port, opt, tty, database, username, password (all char*)

  Description:
    Setup configuration for postgres database connection
*/
Postgres::Postgres( char* host, char* port, char* opt,  char* tty,
                    char* db,   char* user, char* pass) : 
                    host(host), port(port), opt(opt), tty(tty),
                    db(db), user(user), pass(pass) {
  connection = nullptr;
  results    = nullptr;
  clearQuery();
}

/*
  Destructor:   ~Postgres
  Inputs:       None (void)

  Description:
    Ensure postgres connection is safely terminated during object
    destruction
*/
Postgres::~Postgres(void) {
  disconnect();
}

/*
  Function:     connect
  Inputs:       None (void)
  Outputs:      connectionEstablished (bool)

  Description:
    Attempt to establish a connection to a postgres database using the configured 
    parameters.
*/
bool Postgres::connect(void) {
  // Limit to a maximum of 3 attempts
  int counter = 0;
  while (counter < 3) {
    // Attemp connection
    connection = PQsetdbLogin(host.c_str(), port.c_str(), "", "", "dbname = postgres", "postgres", "password");

    // Check connection status
    if (PQstatus(connection) == ConnStatusType::CONNECTION_OK)
      return true; // Connection established

    // Update counter
    ++counter;
  }
  return false; // No connection established
}

/*
  Function:     disconnect
  Inputs:       None (void)

  Description:
    Expected procedure for safe termination of a connection to the postgres
    databse.
*/
void Postgres::disconnect(void) {
  if (PQstatus(connection) == ConnStatusType::CONNECTION_OK)
    PQfinish(connection);
}

/*
  Function:     clearQuery
  Inputs:       None (void)

  Description:
    Clear query buffer of any 
*/
void Postgres::clearQuery(void) {
  memset(queryBuffer, '\0', 100);
}

/*
  Function:     exec
  Inputs:       query (string)
  Outputs:      resultValue (char*)

  Description:
    Execute the provided query
*/
char* Postgres::exec(std::string query) {
  // Prevent function usage if connection is not established
  if (PQstatus(connection) != ConnStatusType::CONNECTION_OK) return NULL;
  results = PQexec(connection, query.c_str());
  return PQgetvalue(results, 0, 0);
}

/*
  Function:     execFunc
  Inputs:       func (string)
  Outputs:      result (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func()"
    where func is the provided database function
*/
char* Postgres::execFunc(std::string func) {
  clearQuery();
  sprintf_s(queryBuffer, "SELECT * FROM %s()", func.c_str());
  return exec(queryBuffer);
}

/*
  Function:     execFunc
  Inputs:       func (char*), id (int)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id)"
    where func is the provided database function and id is the function input
*/
char* Postgres::execFunc(std::string func, int id) {
  clearQuery();
  sprintf_s(queryBuffer, "SELECT * FROM %s(%d)", func.c_str(), id);
  return exec(queryBuffer);
}

/*
  Function:     execFunc
  Inputs:       func (string), ticker (char*)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id)"
    where func is the provided database function and id is the function input
*/
char* Postgres::execFunc(std::string func, std::string ticker) {
  clearQuery();
  sprintf_s(queryBuffer, "SELECT * FROM %s('%s')", func.c_str(), ticker.c_str());
  return exec(queryBuffer);
}

/*
  Function:     execFunc
  Inputs:       func (string), ticker (string), num (int)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id, num)"
    where func is the provided database function and id & num are the function inputs
*/
char* Postgres::execFunc(std::string func, std::string ticker, int num) {
  clearQuery();
  sprintf_s(queryBuffer, "SELECT * FROM %s('%s', %d)", func.c_str(), ticker.c_str(), num);
  return exec(queryBuffer);
}

/*
  Function:     getNetworkCount
  Inputs:       None (void)
  Output:       count (int)

  Description:
    Obtain the total count of networks in the database
*/
int Postgres::getNetworkCount(void) {
  // Database response
  std::string valueStr = execFunc("network_count");
  return toInt(valueStr.c_str());
}

/*
  Function:     getNetwork
  Inputs:       id (size_t)
  Outputs:      ticker (char*)

  Description:
    Obtain the ticker symbol associated with the provided id
*/
std::string Postgres::getNetwork(size_t id) {
  if ((id < 1) || (id > getNetworkCount())) return NULL;
  return execFunc("get_network", id);
}

/*
  Function:     layerCount
  Inputs:       ticker (string)
  Outputs:      count (int)

  Description:
    Obtain the expected layer count for each neural network in the database
*/
int Postgres::getLayerCount(std::string ticker) {
  std::string valueStr = execFunc("layer_count", ticker.c_str());
  return toInt(valueStr);
}

/*
  Function:     getInputs
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request specifying how many inputs are present for the layer
*/
int Postgres::getInputs(std::string ticker, int layerNum) {
  std::string valueStr = execFunc("layer_inputs", ticker.c_str(), layerNum);
  return toInt(valueStr);
}

/*
  Function:     getNodes
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request specifying how many nodes are present for the layer
*/
int Postgres::getNodes(std::string ticker, int layerNum) {
  std::string valueStr = execFunc("layer_nodes", ticker.c_str(), layerNum);
  return toInt(valueStr);
}

/*
  Function:     getIndex
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request for specific layer index to mark when to search for
    weight and bias values within the database
*/
int Postgres::getIndex(std::string ticker, int layerNum) {
  std::string valueStr = execFunc("layer_index", ticker.c_str(), layerNum);
  return toInt(valueStr);
}

/*
  Function:     getLayer
  Inputs:       ticker (string), layerNum (int)

  Description:
    SQL request for all configurations parameters for a specified layer within the
    requested network.
*/
LayerConfiguration Postgres::getLayer(std::string ticker, unsigned int layerNum) {
  LayerConfiguration layer;


  return layer;
}

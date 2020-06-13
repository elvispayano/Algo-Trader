/*
  Title:
    PG Connect

  Description:
    This class is responsible for configuring and managing
    the connection to the PostgreSQL database. The main objective
    of this class is to ensure that when a request is made, there
    is a valid connection.

  Tests:
    test_pg_connect.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_connect.h"

/*
  Constructor:    PGConnect
  Inputs:         None (void)

  Description:
    Configure postgres connection parameters with default values
    that are commonly used in introductory databases
*/
PGConnect::PGConnect(void) {
  // Default postgres settings
  host     = "localhost";
  port     = "5432";
  database = "dbname = postgres";
  username = "postgres";
  password = "password";
  options  = "";
  tty      = "";

  // Initalize pointers
  connection = nullptr;
  result     = nullptr;
  
  // Connection not yet established
  connected = false;
}

/*
  Destructor:   ~PGConnect
  Inputs:       None (void)

  Description:
    Ensure postgres connection is safely terminated during object
    destruction.
*/
PGConnect::~PGConnect(void) {
  disconnect();
}

/*
  Function:     connect
  Inputs:       None (void)

  Description:
    Attempt to establish a connection to a postgres database using
    the configured parameters
*/
void PGConnect::connect(void) {
  // Ensure a connection has not previously been established
  if (isConnected()) return;

  // Attempt database connection
  connection = PQsetdbLogin(host, port, options, tty, database, username, password);

  // Ensure connection has been established
  if (getStatus() != CONNECTION_OK) {
    // Report failed connection
    printf("Connection Failed:\n\t%s\n",PQerrorMessage(connection));
    return;
  }

  // Record connection established
  connected = true;
}

/*
  Function:     disconnect
  Inputs:       None (void)

  Description:
    Safely terminate an established connection to a postgres database
*/
void PGConnect::disconnect(void) {
  // Disconnect only if a connection has been previously established
  if (isConnected()) {
    PQfinish(connection);

    // Record connection terminated
    connected = false;
  }
}

/*
  Function:     getStatus
  Inputs:       None (void)
  Outputs:      status (ConnStatusType)

  Description:
    Get the recorded status for the current postgres connection
*/
ConnStatusType PGConnect::getStatus(void) {
  return PQstatus(connection);
}

/*
  Function:     exec
  Inputs:       query (char*)
  Outputs:      resultValue (char*)

  Description:
    Execute the provided query
*/
char* PGConnect::exec(char* query) {
  // Prevent function usage if connection is not established
  if (getStatus() != ConnStatusType::CONNECTION_OK) return NULL;
  result = PQexec(connection, query);
  return PQgetvalue(result, 0, 0);
}

/*
  Function:     execFunc
  Inputs:       func (char*)
  Outputs:      result (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func()"
    where func is the provided database function
*/
char* PGConnect::execFunc(char* func) {
  char query[40];
  sprintf_s(query, "SELECT * FROM %s()", func);
  return exec(query);
}

/*
  Function:     execFunc
  Inputs:       func (const char*), id (int)
  Outputs:      results (char*)

  Description:
    Execute the provided function using the format
      "SELECT * FROM func(id)"
    where func is the provided database function and id is the function input
*/
char* PGConnect::execFunc(char* func, int id) {
  char query[40];
  sprintf_s(query, "SELECT * FROM %s(%d)", func, id);
  return exec(query);
}

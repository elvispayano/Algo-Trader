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

#ifndef PG_CONNECT_H
#define PG_CONNECT_H

// Postgres Includes
#include <libpq-fe.h>

class PGConnect {
public:
  // Constructor
  PGConnect(void);
  
  // Destructor
  ~PGConnect(void);

  // Status Indication Functions
  ConnStatusType getStatus(void);
  bool isConnected(void) { return connected; }

protected:
  // Configure connection
  void setHost    (const char* host)     { this->host     = host;     };
  void setPort    (const char* port)     { this->port     = port;     };
  void setOptions (const char* options)  { this->options  = options;  };
  void setTTY     (const char* tty)      { this->tty      = tty;      };
  void setDatabase(const char* database) { this->database = database; };
  void setUsername(const char* username) { this->username = username; };
  void setPassword(const char* password) { this->password = password; };

  // Establish or Terminate Connection
  void connect(void);
  void disconnect(void);

private:
  // Connection parameters
  const char* host;
  const char* port;
  const char* database;
  const char* username;
  const char* password;
  const char* options;
  const char* tty;

  // Postgres Connection
  PGconn* connection;
  PGresult* result;

  bool connected;
};

#endif /* PG_CONNECT_H */

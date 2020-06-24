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

// Standard Includes
#include <string>

// Forward Declarations
class pg_conn;
class pg_result;

class PGConnect {
public:
  // Constructor
  PGConnect(void);
  
  // Destructor
  ~PGConnect(void);

  // Status Indication Functions
  size_t getStatus(void);
  virtual bool isConnected(void) { return connected; }

  // SQL Interface Functions
  virtual char* execFunc(char* func);
  virtual char* execFunc(char* func, int id);
  virtual char* execFunc(char* func, char* ticker);
  virtual char* execFunc(std::string func, char* ticker, int num);

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

  // Common Conversions
  virtual int pg2i(std::string input);
  virtual float pg2f(std::string input);

  // Postgres Connection
  pg_conn* connection;
  pg_result* result;

  // Table to query
  const char* table;

private:
  // Execute query
  char* exec(char* query);

  // Connection parameters
  const char* host;
  const char* port;
  const char* database;
  const char* username;
  const char* password;
  const char* options;
  const char* tty;

  bool connected;
};

#endif /* PG_CONNECT_H */

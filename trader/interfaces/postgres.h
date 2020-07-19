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

#ifndef POSTGRES_H
#define POSTGRES_H

// Interface Includes
#include "database_base.h"

// Utilities Includes
#include "network_types.h"

// Forward Declaration
struct pg_conn;
struct pg_result;

class Postgres : public DatabaseBase {
public:
  Postgres(char* host, char* port, char* tty, char* opt, char* db, char* user, char* pass);   // Constructor
  ~Postgres(void);  // Destructor

  // Connection management
  bool connect(void) override;
  void disconnect(void) override;
  
  // Network configuration
  int getNetworkCount(void) override;
  std::string getNetwork(size_t id) override;
  int getLayerCount(std::string ticker) override;

  // Layer configuration
  LayerConfiguration getLayer(std::string ticker, unsigned int layerNum) override;

private:
  int getInputs(std::string ticker, int layerNum);
  int getNodes(std::string ticker, int layerNum);
  int getIndex(std::string ticker, int layerNum);
  double getWeightBias(std::string ticker, int index);
  ActivationTypes getActivation(std::string ticker, int layerNum);
  LayerTypes getLayerType(std::string ticker, int layerNum);

  void clearQuery(void);

  char* execFunc(std::string func);
  char* execFunc(std::string func, int num);
  char* execFunc(std::string func, std::string ticker);
  char* execFunc(std::string func, std::string ticker, int num);

  char* exec(std::string in);

  pg_conn*   connection;
  pg_result* results;

  char queryBuffer[100];

  std::string host, port, tty, opt, db, user, pass;
};

#endif /* POSTGRES_H */

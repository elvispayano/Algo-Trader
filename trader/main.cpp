// trader.cpp : Defines the entry point for the application.
//
#ifdef DEBUG
#include "test_main.h"
#endif

#include "main.h"
#include "postgres.h"

int main(int argc, char **argv) {
#ifdef DEBUG
  test_main();
#endif

  // Configure database connection
  database = new Postgres("localhost", "5432", "", "", "dbname = postgres", "postgres", "password");
  if (!database->connect())
    return 1;


  
  // Memory Cleanup
  if (database) delete database;
  return 0;
}

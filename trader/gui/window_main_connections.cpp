
// Interface Includes
#include "broker_base.h"
#include "database_base.h"
#include "interactive_broker.h"
#include "ib_wrapper.h"
#include "postgres.h"

// QT Includes
#include "window_main.h"
#include "ui_window_main.h"

void WindowMain::onPostgreSQLActionTriggered(void) {
  onDatabaseDisconnectTriggered();

  printf("Configuring PostgreSQL Connection\n");
  database = new Postgres("localhost", "5432", "", "", "dbname = trader", "postgres", "password");
}

void WindowMain::onInteractiveBrokerActionTriggered(void) {
  onBrokerDisconnectTriggered();
  
  ui->statusbar->showMessage("Connecting to Interactive Broker...");
  broker = new InteractiveBroker(new IBWrapper("127.0.0.1", 6550, 0));
}

void WindowMain::onDatabaseDisconnectTriggered(void) {
  if (!database)
    return;

  database->disconnect();
  delete database;
  database = 0;
}

void WindowMain::onBrokerDisconnectTriggered(void) {
  if (!broker)
    return;

  ui->statusbar->showMessage("Broker Disconnecting");
  broker->terminateConnection();
  delete broker;
  broker = 0;
}
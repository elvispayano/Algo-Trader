
// Interface Includes
#include "broker_base.h"
#include "database_base.h"
#include "interactive_broker.h"
#include "ib_wrapper.h"
#include "postgres.h"

// QT Includes
#include "dialog_postgres.h"
#include "window_main.h"
#include "ui_window_main.h"

void WindowMain::onPostgreSQLActionTriggered(void) {
  onDatabaseDisconnectTriggered();

  ui->statusbar->showMessage("Connecting to PostgreSQL Database...");
  DialogPostgres dialog;
  dialog.show();
  dialog.exec();
  
  if (dialog.isConnected()) {
    ui->statusbar->showMessage("Could not establish connection to PostgreSQL Database");
    return;
  }
  database = dialog.getDatabase();
  ui->statusbar->showMessage("PostgreSQL Connection Established");
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

  broker->terminateConnection();
  delete broker;
  broker = 0;
}
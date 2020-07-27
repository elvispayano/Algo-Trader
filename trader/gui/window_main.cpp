// Interface Includes
#include "broker_base.h"
#include "database_base.h"

// GUI Includes
#include "window_main.h"
#include "ui_window_main.h"

WindowMain::WindowMain(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::WindowMain)
{
  ui->setupUi(this);

  /*
  Toolbar mapping
  */

  // Run mapping
  QObject::connect(ui->actionUnitTests, SIGNAL(triggered()), this, SLOT(onUnitTestsActionTiggered()));

  // Connection mapping
  QObject::connect(ui->actionConnectPostgreSQL, SIGNAL(triggered()), this, SLOT(onPostgreSQLActionTriggered()));
  QObject::connect(ui->actionDatabaseDisconnect, SIGNAL(triggered()), this, SLOT(onDatabaseDisconnectTriggered()));
  QObject::connect(ui->actionConnectInteractiveBroker, SIGNAL(triggered()), this, SLOT(onInteractiveBrokerActionTriggered()));
  QObject::connect(ui->actionBrokerDisconnect, SIGNAL(triggered()), this, SLOT(onBrokerDisconnectTriggered()));

  // Button mapping
  QObject::connect(ui->pushRunButton, SIGNAL(released()), this, SLOT(run()));

  database = 0;
  broker = 0;
}

WindowMain::~WindowMain()
{
  delete ui;

  onDatabaseDisconnectTriggered();
  onBrokerDisconnectTriggered();
}

void WindowMain::run(void) {
  if (!database) {
    ui->statusbar->showMessage("Error: No Database Connection");
    return;
  }

  if (!broker) {
    ui->statusbar->showMessage("Error: No Broker Connection");
    return;
  }

  database->connect();
  broker->connectionManager();
}

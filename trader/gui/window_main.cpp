/*
  Title:
    Main Window

  Description:
    The main window functionality and configuration specifications for
    the trader user interface

  Author:
    Elvis Payano
*/

// Interface Includes
#include "broker_base.h"
#include "database_base.h"

// Neural Networks
#include "neural_network.h"

// GUI Includes
#include "dialog_network_create.h"
#include "ui_window_main.h"
#include "window_main.h"

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
  QObject::connect(ui->pushCreate, SIGNAL(released()), this, SLOT(create()));

  database = 0;
  broker = 0;

  createdNetworks.clear();
  trainedNetworks.clear();
  activeNetworks.clear();
}

WindowMain::~WindowMain()
{
  delete ui;

  onDatabaseDisconnectTriggered();
  onBrokerDisconnectTriggered();

  for (int ind = 0; ind < createdNetworks.size(); ++ind) {
    if (createdNetworks[ind])
      delete createdNetworks[ind];
  }
  createdNetworks.clear();
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

void WindowMain::create(void) {
  // Require a an active database connection
  if (!database) {
    ui->statusbar->showMessage("Error: Requires Database Connection");
    return;
  }

  // Run and update loaded networks
  DialogNetworkCreate dialog;
  dialog.show();
  dialog.exec();

  createdNetworks.push_back(dialog.getNetwork());
}

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
#include <QtWidgets/QPlainTextEdit>
#include "dialog_network_create.h"
#include "ui_window_main.h"
#include "window_main.h"

// Standard Includes
#include <string>

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
  QObject::connect(ui->pushDelete, SIGNAL(released()), this, SLOT(destroy()));

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

  if (!dialog.networkReady())
    return;

  createdNetworks.push_back(dialog.getNetwork());
  updateNetworkTables();
}

void WindowMain::destroy(void) {
  std::vector<NeuralNetwork*>::iterator it = createdNetworks.begin() + ui->tableCreatedNetworks->currentRow();;
  createdNetworks.erase(it);

  updateCreatedNetworks();
}

void WindowMain::updateNetworkTables(void) {
  // Update created networks table
  updateCreatedNetworks();
}

void WindowMain::updateCreatedNetworks(void) {
  // Download any existing networks from database


  // Upload network to database


  // Update Gui Table
  ui->tableCreatedNetworks->clearContents();

  int rows = createdNetworks.size();
  for (int ind = 0; ind < rows; ++ind) {
    ui->tableCreatedNetworks->insertRow(ind);

    QPlainTextEdit* symbol = newTextBox(createdNetworks[ind]->getTicker());
    ui->tableCreatedNetworks->setCellWidget(ind, 0, symbol);

    QPlainTextEdit* layers = newTextBox(std::to_string(createdNetworks[ind]->getLayerCount()));
    ui->tableCreatedNetworks->setCellWidget(ind, 1, layers);

    QPlainTextEdit* nodes = newTextBox(std::to_string(createdNetworks[ind]->getTotalNodes()));
    ui->tableCreatedNetworks->setCellWidget(ind, 2, nodes);
  }

  for (int ind = 0; ind < ui->tableCreatedNetworks->rowCount(); ++ind)
    if (ind >= createdNetworks.size())
      ui->tableCreatedNetworks->removeRow(ind);

}

QPlainTextEdit* WindowMain::newTextBox(std::string input) {
  QString inputText(input.c_str());
  
  QPlainTextEdit* textbox = new QPlainTextEdit();
  textbox->setReadOnly(true);
  textbox->setPlainText(inputText);

  return textbox;
}
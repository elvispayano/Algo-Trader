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

  // Created button mapping
  QObject::connect(ui->pushCreate, SIGNAL(released()), this, SLOT(onCreateReleased()));
  QObject::connect(ui->pushDelete, SIGNAL(released()), this, SLOT(onDeleteReleased()));
  QObject::connect(ui->pushTrain,  SIGNAL(released()), this, SLOT(onTrainReleased()));

  database = 0;
  broker = 0;

  networkCreated.clear();
  trainedNetworks.clear();
  activeNetworks.clear();
}

WindowMain::~WindowMain()
{
  delete ui;

  onDatabaseDisconnectTriggered();
  onBrokerDisconnectTriggered();

  // Created Networks memory cleanup
  for (std::map<std::string, NeuralNetwork*>::iterator it = networkCreated.begin(); it != networkCreated.end(); ++it)
    delete it->second;

  networkCreated.clear();
}

void WindowMain::updateNetworkTables(void) {
  // Update created networks table
  updateCreatedNetworks();
}

QPlainTextEdit* WindowMain::newTextBox(std::string input) {
  QString inputText(input.c_str());
  
  QPlainTextEdit* textbox = new QPlainTextEdit();
  textbox->setReadOnly(true);
  textbox->setPlainText(inputText);

  return textbox;
}

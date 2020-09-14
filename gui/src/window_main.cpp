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
#include <QtWidgets/QPlainTextEdit>

// Standard Includes
#include <string>

WindowMain::WindowMain( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::WindowMain ) {
  ui->setupUi( this );

  /*
  Toolbar mapping
  */

  // Run mapping
  QObject::connect( ui->actionUnitTests,
                    SIGNAL( triggered() ),
                    this,
                    SLOT( onUnitTestsActionTiggered() ) );

  // Connection mapping
  QObject::connect( ui->actionConnectPostgreSQL,
                    SIGNAL( triggered() ),
                    this,
                    SLOT( onPostgreSQLActionTriggered() ) );
  QObject::connect( ui->actionDatabaseDisconnect,
                    SIGNAL( triggered() ),
                    this,
                    SLOT( onDatabaseDisconnectTriggered() ) );
  QObject::connect( ui->actionConnectInteractiveBroker,
                    SIGNAL( triggered() ),
                    this,
                    SLOT( onInteractiveBrokerActionTriggered() ) );
  QObject::connect( ui->actionBrokerDisconnect,
                    SIGNAL( triggered() ),
                    this,
                    SLOT( onBrokerDisconnectTriggered() ) );

  // Button mapping
  QObject::connect(
      ui->pushCreate, SIGNAL( released() ), this, SLOT( create() ) );
  QObject::connect(
      ui->pushDelete, SIGNAL( released() ), this, SLOT( destroy() ) );

  database = 0;
  broker   = 0;

  networkCreated.clear();
  trainedNetworks.clear();
  activeNetworks.clear();
}

WindowMain::~WindowMain() {
  delete ui;

  onDatabaseDisconnectTriggered();
  onBrokerDisconnectTriggered();

  for ( std::map< std::string, NeuralNetwork* >::iterator it =
            networkCreated.begin();
        it != networkCreated.end();
        ++it ) {
    delete it->second;
    networkCreated.erase( it->first );
  }
}

void WindowMain::run( void ) {
  if ( !database ) {
    ui->statusbar->showMessage( "Error: No Database Connection" );
    return;
  }

  if ( !broker ) {
    ui->statusbar->showMessage( "Error: No Broker Connection" );
    return;
  }

  database->connect();
  broker->connectionManager();
}

void WindowMain::create( void ) {
  // Require a an active database connection
  if ( !database ) {
    ui->statusbar->showMessage( "Error: Requires Database Connection" );
    return;
  }

  // Run and update loaded networks
  DialogNetworkCreate dialog;
  dialog.show();
  dialog.exec();

  if ( !dialog.networkReady() )
    return;

  NeuralNetwork* network = dialog.getNetwork();
  std::string    ticker  = network->getTicker();
  if ( networkCreated.find( ticker ) != networkCreated.end() ) {
    delete networkCreated[ticker];
    networkCreated.erase( ticker );
  }
  networkCreated[network->getTicker()] = dialog.getNetwork();

  updateNetworkTables();
}

void WindowMain::destroy( void ) {
  int row = ui->tableCreatedNetworks->currentRow();
  if ( row >= networkCreated.size() )
    return;

  std::string ticker = static_cast< QPlainTextEdit* >(
                           ui->tableCreatedNetworks->cellWidget( row, 0 ) )
                           ->toPlainText()
                           .toStdString();

  if ( networkCreated.find( ticker ) != networkCreated.end() ) {
    delete networkCreated[ticker];
    networkCreated.erase( ticker );
  }

  updateCreatedNetworks();
}

void WindowMain::updateNetworkTables( void ) {
  // Update created networks table
  updateCreatedNetworks();
}

void WindowMain::updateCreatedNetworks( void ) {
  // Update Gui Table
  ui->tableCreatedNetworks->clearContents();

  int row = 0;
  for ( std::map< std::string, NeuralNetwork* >::iterator it =
            networkCreated.begin();
        it != networkCreated.end();
        ++it ) {
    ui->tableCreatedNetworks->insertRow( row );
    std::string ticker = it->second->getTicker();

    // Ticker
    ui->tableCreatedNetworks->setCellWidget( row, 0, newTextBox( ticker ) );

    // Layer Count
    ui->tableCreatedNetworks->setCellWidget(
        row, 1, newTextBox( std::to_string( it->second->getLayerCount() ) ) );

    // Total Nodes
    ui->tableCreatedNetworks->setCellWidget(
        row, 1, newTextBox( std::to_string( it->second->getTotalNodes() ) ) );

    // Increment Row
    ++row;
  }

  for ( row; row < ui->tableCreatedNetworks->rowCount(); ++row )
    ui->tableCreatedNetworks->removeRow( row );
}

QPlainTextEdit* WindowMain::newTextBox( std::string input ) {
  QString inputText( input.c_str() );

  QPlainTextEdit* textbox = new QPlainTextEdit();
  textbox->setReadOnly( true );
  textbox->setPlainText( inputText );

  return textbox;
}

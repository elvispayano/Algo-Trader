/*
  Title:
    Main Window (Created Tab)

  Description:
    The main window created tab functionality that handles creating,
    configuring, and organizing newly created neural networks

  Author:
    Elvis Payano
*/

// Neural Networks
#include "neural_network.h"

// Gui Includes
#include "dialog_network_create.h"
#include "ui_window_main.h"
#include "window_main.h"

// QT Includes
#include <QtWidgets/QPlainTextEdit>

/*
  Function:     onCreateReleased
  Description:
    Creation of a new Neural Network in which the user specifies the
    desired configuration
*/
void WindowMain::onCreateReleased(void) {
  // Run and update loaded networks
  DialogNetworkCreate dialog;
  dialog.show();
  dialog.exec();

  // Check if network was created
  if (!dialog.networkReady())
    return;

  // Gather network data
  NeuralNetwork* network = dialog.getNetwork();
  std::string ticker = network->getTicker();

  // Ensure no duplicate networks are in the map
  if (networkCreated.find(ticker) != networkCreated.end()) {
    delete networkCreated[ticker];
    networkCreated.erase(ticker);
  }

  // Add created network to map
  networkCreated[network->getTicker()] = dialog.getNetwork();

  updateNetworkTables();
}

/*
  Function:     onDeleteReleased
  Description:
    Removal of the selected Neural Network
*/
void WindowMain::onDeleteReleased(void) {
  int row = ui->tableCreatedNetworks->currentRow();
  if (row >= networkCreated.size())
    return;

  std::string ticker = static_cast<QPlainTextEdit*>(ui->tableCreatedNetworks->cellWidget(row, 0))->toPlainText().toStdString();

  if (networkCreated.find(ticker) != networkCreated.end()) {
    delete networkCreated[ticker];
    networkCreated.erase(ticker);
  }

  updateCreatedNetworks();
}

/*
  Function:     onTrainReleased
  Description:
    Start training for the selected Neural Network and promote network
    to the trained network list
*/
void WindowMain::onTrainReleased(void) {

}

/*
  Function:     updateCreatedNetworks
  Description:
    Update the created network table with the latest configuration that
    is present
*/
void WindowMain::updateCreatedNetworks(void) {
  // Update Gui Table
  ui->tableCreatedNetworks->clearContents();

  int row = 0;
  for (std::map<std::string, NeuralNetwork*>::iterator it = networkCreated.begin(); it != networkCreated.end(); ++it) {
    ui->tableCreatedNetworks->insertRow(row);
    std::string ticker = it->second->getTicker();

    // Ticker
    ui->tableCreatedNetworks->setCellWidget(row, 0, newTextBox(ticker));

    // Layer Count
    ui->tableCreatedNetworks->setCellWidget(row, 1, newTextBox(std::to_string(it->second->getLayerCount())));

    // Total Nodes
    ui->tableCreatedNetworks->setCellWidget(row, 2, newTextBox(std::to_string(it->second->getTotalNodes())));

    // Increment Row
    ++row;
  }

  for (row; row < ui->tableCreatedNetworks->rowCount(); ++row)
    ui->tableCreatedNetworks->removeRow(row);
}

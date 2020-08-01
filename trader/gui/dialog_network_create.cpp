// Neural Network Includes
#include "neural_network.h"

// Utility Includes
#include "network_types.h"

// QT Includes
#include <qcombobox.h>
#include <qspinbox.h>
#include "dialog_network_create.h"
#include "ui_dialog_network_create.h"

DialogNetworkCreate::DialogNetworkCreate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNetworkCreate)
{
  ui->setupUi(this);
  ui->textTicker->clear();

  // Layer count modification
  QObject::connect(ui->pushAdd, SIGNAL(released()), this, SLOT(onAddReleased()));
  QObject::connect(ui->pushRemove, SIGNAL(released()), this, SLOT(onRemoveReleased()));

  // Layer order modification
  QObject::connect(ui->pushUp, SIGNAL(released()), this, SLOT(onUpReleased()));
  QObject::connect(ui->pushDown, SIGNAL(released()), this, SLOT(onDownReleased()));

  // Accept/Reject
  QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(networkAccepted()));
  QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(networkRejected()));
  
  // Build Layer Types List
  layerTypeList.push_back("Fully Connected");
  
  // Build Activation Types List
  activationTypeList.push_back("Linear");
  activationTypeList.push_back("Binary");
  activationTypeList.push_back("ReLu");
  activationTypeList.push_back("HTan");
  activationTypeList.push_back("Sigmoid");

  ui->tableNetwork->clearContents();
  network = 0;

  // Layer Map Creation
  layerMap["Fully Connected"] = LayerTypes::FULLYCONNECTED;

  // Activation Map Creation
  activationMap["Linear"] = ActivationTypes::LINEAR;
  activationMap["Binary"] = ActivationTypes::BINARY;
  activationMap["ReLu"] = ActivationTypes::RELU;
  activationMap["HTan"] = ActivationTypes::TANH;
  activationMap["Sigmoid"] = ActivationTypes::SIGMOID;

  newNetwork = false;
}

DialogNetworkCreate::~DialogNetworkCreate()
{
  delete ui;
}

void DialogNetworkCreate::onAddReleased(void) {
  int row = ui->tableNetwork->rowCount();
  ui->tableNetwork->insertRow(row);

  QComboBox* layerCombo = new QComboBox();
  layerCombo->addItems(layerTypeList);
  ui->tableNetwork->setCellWidget(row, 0, layerCombo);

  QComboBox* activationCombo = new QComboBox();
  activationCombo->addItems(activationTypeList);
  ui->tableNetwork->setCellWidget(row, 1, activationCombo);

  QSpinBox* nodeBox = new QSpinBox();
  ui->tableNetwork->setCellWidget(row, 2, nodeBox);
}

void DialogNetworkCreate::onRemoveReleased(void) {
  // Selected row
  int rowCount = ui->tableNetwork->rowCount() - 1;
  int curRow = ui->tableNetwork->currentRow();
  int row = (curRow != -1) ? (curRow) : (rowCount);

  // Interact with the Widget
  ui->tableNetwork->removeRow(row);
  ui->tableNetwork->setCurrentCell(rowCount - 1, 0);
}

void DialogNetworkCreate::onUpReleased(void) {
  int curRow = ui->tableNetwork->currentRow();
  swapRow(curRow, curRow - 1);
}

void DialogNetworkCreate::onDownReleased(void) {
  int curRow = ui->tableNetwork->currentRow();
  swapRow(curRow, curRow + 1);
}

void DialogNetworkCreate::swapRow(int x, int y) {
  for (int i = 0; i < ui->tableNetwork->columnCount(); ++i) {
    if (i == 2) {
      QSpinBox* box1 = static_cast<QSpinBox*>(ui->tableNetwork->cellWidget(x, i));
      QSpinBox* box2 = static_cast<QSpinBox*>(ui->tableNetwork->cellWidget(y, i));

      int val1 = box1->value();
      int val2 = box2->value();

      box1->setValue(val2);
      box2->setValue(val1);
    }
    else {
      QComboBox* box1 = static_cast<QComboBox*>(ui->tableNetwork->cellWidget(x, i));
      QComboBox* box2 = static_cast<QComboBox*>(ui->tableNetwork->cellWidget(y, i));

      QString val1 = box1->currentText();
      QString val2 = box2->currentText();

      box1->setCurrentText(val2);
      box2->setCurrentText(val1);
    }
  }
}

void DialogNetworkCreate::networkAccepted(void) {
  // Initialization
  LayerConfiguration config;
  const int totalLayerCount = ui->tableNetwork->rowCount();
  std::string ticker = ui->textTicker->toPlainText().toStdString();

  // Configuration Checking
  if ((totalLayerCount == 0) || ticker.empty()) {
    return;
  }

  network = new NeuralNetwork("MSFT");
  for (int layerInd = 0; layerInd < totalLayerCount; ++layerInd) {
    // Layer Type
    QString layer = static_cast<QComboBox*>(ui->tableNetwork->cellWidget(layerInd, 0))->currentText();
    if (layerMap.find(layer) != layerMap.end())
      config.Layer = layerMap[layer];
    else
      config.Layer = LayerTypes::UNKNOWN;
    
    // Activation Type
    QString activation = static_cast<QComboBox*>(ui->tableNetwork->cellWidget(layerInd, 1))->currentText();
    if (activationMap.find(activation) != activationMap.end())
      config.Activation = activationMap[activation];
    else
      config.Activation = ActivationTypes::UNKNOWN;

    // Inputs
    if (layerInd == 0)
      config.layerWidth = 4;
    else
      config.layerWidth = config.layerHeight;

    // Nodes
    if (layerInd == totalLayerCount)
      config.layerHeight = 3;
    else
      config.layerHeight = static_cast<QSpinBox*>(ui->tableNetwork->cellWidget(layerInd, 2))->value();

    network->addLayer(config);
  }

  newNetwork = true;
  this->close();
}

void DialogNetworkCreate::networkRejected(void) {
  if (network) {
    delete network;
    network = 0;
  }

  ui->tableNetwork->clearContents();

  this->close();
}

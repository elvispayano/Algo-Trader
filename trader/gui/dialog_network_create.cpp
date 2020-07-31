#include <qcombobox.h>
#include <qspinbox.h>

#include "dialog_network_create.h"
#include "ui_dialog_network_create.h"

DialogNetworkCreate::DialogNetworkCreate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNetworkCreate)
{
  ui->setupUi(this);

  QObject::connect(ui->pushAdd, SIGNAL(released()), this, SLOT(onAddReleased()));
  QObject::connect(ui->pushRemove, SIGNAL(released()), this, SLOT(onRemoveReleased()));
  QObject::connect(ui->pushUp, SIGNAL(released()), this, SLOT(onUpReleased()));
  QObject::connect(ui->pushDown, SIGNAL(released()), this, SLOT(onDownReleased()));

  ui->tableNetwork->clearContents();
  
  // Build Layer Types List
  layerTypeList.push_back("Fully Connected");
  
  // Build Activation Types List
  activationTypeList.push_back("Linear");
  activationTypeList.push_back("Binary");
  activationTypeList.push_back("ReLu");
  activationTypeList.push_back("HTan");
  activationTypeList.push_back("Sigmoid");
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

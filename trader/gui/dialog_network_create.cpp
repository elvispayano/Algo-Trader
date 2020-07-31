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

}

DialogNetworkCreate::~DialogNetworkCreate()
{
  delete ui;
}

void DialogNetworkCreate::onAddReleased(void) {
  QTableWidgetItem* item = new QTableWidgetItem(1);
  int row = ui->tableNetwork->rowCount();
  ui->tableNetwork->insertRow(row);
  ui->tableNetwork->setItem(row, 0, item);
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
  QList<QTableWidgetItem*> curList;

  getRow(curList, curRow);
  setRow(curList, curRow-1);
}

void DialogNetworkCreate::onDownReleased(void) {
  int curRow = ui->tableNetwork->currentRow();
  QList<QTableWidgetItem*> curList;

  getRow(curList, curRow);
  setRow(curList, curRow + 1);
}

void DialogNetworkCreate::getRow(QList<QTableWidgetItem*>& list, int row) {
  list.clear();

  for (int i = 0; i < ui->tableNetwork->columnCount(); ++i)
    list.push_back(ui->tableNetwork->takeItem(row, i));

  ui->tableNetwork->removeRow(row);
}

void DialogNetworkCreate::setRow(QList<QTableWidgetItem*>& list, int row) {
  ui->tableNetwork->insertRow(row);

  for (int i = 0; i < ui->tableNetwork->columnCount(); ++i)
    ui->tableNetwork->setItem(row, i, list[i]);
}

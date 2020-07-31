#include "dialog_network_create.h"
#include "ui_dialog_network_create.h"

DialogNetworkCreate::DialogNetworkCreate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNetworkCreate)
{
  ui->setupUi(this);

  QObject::connect(ui->pushAdd, SIGNAL(released()), this, SLOT(onAddReleased()));
  QObject::connect(ui->pushRemove, SIGNAL(released()), this, SLOT(onRemoveReleased()));

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

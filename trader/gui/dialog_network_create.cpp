#include "dialog_network_create.h"
#include "ui_dialog_network_create.h"

DialogNetworkCreate::DialogNetworkCreate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNetworkCreate)
{
  ui->setupUi(this);
}

DialogNetworkCreate::~DialogNetworkCreate()
{
  delete ui;
}

#include "postgres.h"

#include "dialog_postgres.h"
#include "ui_dialog_postgres.h"

DialogPostgres::DialogPostgres(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogPostgres)
{
  ui->setupUi(this);

  // Initialization
  database = 0;
  host.clear();
  port.clear();
  opt.clear();
  tty.clear();
  db.clear();
  user.clear();
  password.clear();

  // Button actions
  QObject::connect(ui->pushConnect, SIGNAL(released()), this, SLOT(connectReleased()));
  QObject::connect(ui->pushCancel, SIGNAL(released()), this, SLOT(cancelReleased()));
  QObject::connect(ui->textHost, SIGNAL(textChanged()), this, SLOT(updateHost()));
  QObject::connect(ui->textPort, SIGNAL(textChanged()), this, SLOT(updatePort()));
  QObject::connect(ui->textOptions, SIGNAL(textChanged()), this, SLOT(updateOptions()));
  QObject::connect(ui->textTTY, SIGNAL(textChanged()), this, SLOT(updateTTY()));
  QObject::connect(ui->textDatabase, SIGNAL(textChanged()), this, SLOT(updateDatabase()));
  QObject::connect(ui->textUsername, SIGNAL(textChanged()), this, SLOT(updateUsername()));
  QObject::connect(ui->textPassword, SIGNAL(textChanged()), this, SLOT(updatePassword()));

  // Clear Fields
  ui->textHost->clear();
  ui->textPort->clear();
  ui->textDatabase->clear();
  ui->textUsername->clear();
  ui->textPassword->clear();
}

DialogPostgres::~DialogPostgres()
{
  delete ui;
}

void DialogPostgres::connectReleased(void) {
  
  if (host.empty() || port.empty() || db.empty() || user.empty() || password.empty()) {
    return;
  }
  database = new Postgres((char*) host.c_str(), (char*) port.c_str(),
                          (char*) opt.c_str(),  (char*) db.c_str(), (char*)db.c_str(), 
                          (char*) user.c_str(), (char*) password.c_str());

  if (!database->connect()) {
    //TODO: Signal incorrect login provided
    return;
  }
  this->close();
}

void DialogPostgres::cancelReleased(void) {
  if (database) {
    delete database;
    database = 0;
  }
  this->close();
}

void DialogPostgres::updateHost(void) {
  host = ui->textHost->toPlainText().toStdString();
}

void DialogPostgres::updatePort(void) {
  port = ui->textPort->toPlainText().toStdString();
}

void DialogPostgres::updateOptions(void) {
  opt = ui->textOptions->toPlainText().toStdString();
}

void DialogPostgres::updateTTY(void) {
  tty = ui->textTTY->toPlainText().toStdString();
}

void DialogPostgres::updateDatabase(void) {
  db = ui->textDatabase->toPlainText().toStdString();
}

void DialogPostgres::updateUsername(void) {
  user = ui->textUsername->toPlainText().toStdString();
}

void DialogPostgres::updatePassword(void) {
  password = ui->textPassword->toPlainText().toStdString();
}

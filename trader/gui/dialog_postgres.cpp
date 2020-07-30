#include "postgres.h"

// QT Includes
#include <QtWidgets/QPlainTextEdit>
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
  // Ensure all required fields are populated
  if (host.empty() || port.empty() || db.empty() || user.empty() || password.empty()) {
    highlight(ui->textHost, Qt::red);
    highlight(ui->textPort, Qt::red);
    highlight(ui->textDatabase, Qt::red);
    highlight(ui->textUsername, Qt::red);
    highlight(ui->textPassword, Qt::red);
    return;
  }

  // Attempt connection to database
  database = new Postgres((char*) host.c_str(), (char*) port.c_str(),
                          (char*) opt.c_str(),  (char*) db.c_str(), (char*)db.c_str(), 
                          (char*) user.c_str(), (char*) password.c_str());
  if (!database->connect()) {
    highlight(ui->textHost, Qt::red);
    highlight(ui->textPort, Qt::red);
    highlight(ui->textDatabase, Qt::red);
    highlight(ui->textUsername, Qt::red);
    highlight(ui->textPassword, Qt::red);
    return;
  }

  // Connection established - close window
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
  highlight(ui->textHost, Qt::white);
  host = ui->textHost->toPlainText().toStdString();
}

void DialogPostgres::updatePort(void) {
  highlight(ui->textPort, Qt::white);
  port = ui->textPort->toPlainText().toStdString();
}

void DialogPostgres::updateOptions(void) {
  highlight(ui->textOptions, Qt::white);
  opt = ui->textOptions->toPlainText().toStdString();
}

void DialogPostgres::updateTTY(void) {
  highlight(ui->textTTY, Qt::white);
  tty = ui->textTTY->toPlainText().toStdString();
}

void DialogPostgres::updateDatabase(void) {
  highlight(ui->textDatabase, Qt::white);
  db = ui->textDatabase->toPlainText().toStdString();
}

void DialogPostgres::updateUsername(void) {
  highlight(ui->textUsername, Qt::white);
  user = ui->textUsername->toPlainText().toStdString();
}

void DialogPostgres::updatePassword(void) {
  highlight(ui->textPassword, Qt::white);
  password = ui->textPassword->toPlainText().toStdString();
}

void DialogPostgres::highlight(QPlainTextEdit* element, Qt::GlobalColor color) {
  QPalette palette = element->palette();
  palette.setColor(element->backgroundRole(), color);
  element->setPalette(palette);
}

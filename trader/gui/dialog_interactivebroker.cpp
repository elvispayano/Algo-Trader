#include "interactive_broker.h"
#include "ib_wrapper.h"

#include "dialog_interactivebroker.h"
#include "ui_dialog_interactivebroker.h"

DialogInteractiveBroker::DialogInteractiveBroker(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogInteractiveBroker)
{
  ui->setupUi(this);

  // Initialization
  host.clear();
  port = 0;
  clientID = 0;

  broker = 0;

  // Button actions
  QObject::connect(ui->pushConnect, SIGNAL(released()), this, SLOT(connectReleased()));
  QObject::connect(ui->pushCancel, SIGNAL(released()), this, SLOT(cancelReleased()));
  QObject::connect(ui->textHost, SIGNAL(textChanged()), this, SLOT(updateHost()));
  QObject::connect(ui->textPort, SIGNAL(textChanged()), this, SLOT(updatePort()));
  QObject::connect(ui->textClientID, SIGNAL(textChanged()), this, SLOT(updateClientID()));
}

DialogInteractiveBroker::~DialogInteractiveBroker()
{
  delete ui;
}

void DialogInteractiveBroker::connectReleased(void) {
  if (host.empty() || port == 0) {
    highlight(ui->textHost, Qt::red);
    highlight(ui->textPort, Qt::red);
    return;
  }

  broker = new InteractiveBroker(new IBWrapper(host, port, clientID));
  broker->connectionManager();

  this->close();
}

void DialogInteractiveBroker::cancelReleased(void) {
  if (broker) {
    delete broker;
    broker = 0;
  }
  this->close();
}

void DialogInteractiveBroker::updateHost(void) {
  highlight(ui->textHost, Qt::white);
  host = ui->textHost->toPlainText().toStdString();
}

void DialogInteractiveBroker::updatePort(void) {
  highlight(ui->textPort, Qt::white);
  port = ui->textPort->toPlainText().toInt();
}

void DialogInteractiveBroker::updateClientID(void) {
  highlight(ui->textClientID, Qt::white);
  clientID = ui->textClientID->toPlainText().toInt();
}

void DialogInteractiveBroker::highlight(QPlainTextEdit* element, Qt::GlobalColor color) {
  QPalette palette = element->palette();
  palette.setColor(element->backgroundRole(), color);
  element->setPalette(palette);
}

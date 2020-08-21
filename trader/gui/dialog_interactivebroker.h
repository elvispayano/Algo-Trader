/*
  Title:
    Dialog Interactive Broker

  Description:
    The dialog functionality and configuration specifications for defining the
    Interactive Broker connection

  Author:
    Elvis Payano
*/

#ifndef DIALOG_INTERACTIVEBROKER_H
#define DIALOG_INTERACTIVEBROKER_H

#include <QDialog>

// Forward Declaration
class BrokerBase;
class QPlainTextEdit;

namespace Ui {
class DialogInteractiveBroker;
}

class DialogInteractiveBroker : public QDialog {
  Q_OBJECT

public:
  explicit DialogInteractiveBroker( QWidget* parent = nullptr );
  ~DialogInteractiveBroker();

  bool        isConnected( void ) { return false; }
  BrokerBase* getBroker( void ) { return NULL; }

public slots:
  void connectReleased( void );
  void cancelReleased( void );

  void updateHost( void );
  void updatePort( void );
  void updateClientID( void );

private:
  void highlight( QPlainTextEdit* obj, Qt::GlobalColor );

  Ui::DialogInteractiveBroker* ui;
  BrokerBase*                  broker;

  std::string host;
  int         port;
  int         clientID;
};

#endif  // DIALOG_INTERACTIVEBROKER_H

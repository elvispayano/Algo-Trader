/*
  Title:
    Main Window

  Description:
    The main window functionality and configuration specifications for
    the trader user interface

  Author:
    Elvis Payano
*/

#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QMainWindow>

namespace Ui {
class WindowMain;
}

class DatabaseBase;
class BrokerBase;

class WindowMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowMain(QWidget *parent = nullptr);
    ~WindowMain();

public slots:
  // Run options
  void onUnitTestsActionTiggered(void);

  // Connection settings
  void onPostgreSQLActionTriggered(void);
  void onInteractiveBrokerActionTriggered(void);
  void onDatabaseDisconnectTriggered(void);
  void onBrokerDisconnectTriggered(void);

  // Button settings
  void run(void);
  void create(void);

private:
    Ui::WindowMain *ui;

    DatabaseBase* database;
    BrokerBase* broker;
};

#endif // WINDOW_MAIN_H

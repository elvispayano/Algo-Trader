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

// QT Includes
#include <QMainWindow>

// Standard Includes
#include <map>
#include <vector>

// Forward Declaration
class QPlainTextEdit;

namespace Ui {
class WindowMain;
}

class BrokerBase;
class DatabaseBase;
class NeuralNetwork;

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

  // Created network button slots
  void onCreateReleased(void);
  void onDeleteReleased(void);
  void onTrainReleased(void);

private:
  void updateNetworkTables(void);
  void updateCreatedNetworks(void);

  QPlainTextEdit* newTextBox(std::string input);

  Ui::WindowMain *ui;

  BrokerBase* broker;
  DatabaseBase* database;
  std::map<std::string, NeuralNetwork*> networkCreated;
  std::vector<NeuralNetwork*> trainedNetworks;
  std::vector<NeuralNetwork*> activeNetworks;
};

#endif // WINDOW_MAIN_H

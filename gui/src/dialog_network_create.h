#ifndef DIALOG_NETWORK_CREATE_H
#define DIALOG_NETWORK_CREATE_H

// Utility Includes
#include "utilities/network_types.h"

// QT Includes
#include <QDialog>

// Standard Includes
#include <map>

// Forward Declaration
class NeuralNetwork;

namespace Ui {
class DialogNetworkCreate;
}

class DialogNetworkCreate : public QDialog {
  Q_OBJECT

public:
  explicit DialogNetworkCreate( QWidget* parent = nullptr );
  ~DialogNetworkCreate();

  NeuralNetwork* getNetwork( void ) { return network; }
  bool           networkReady( void ) { return newNetwork; }

public slots:
  void onAddReleased( void );
  void onRemoveReleased( void );

  void onUpReleased( void );
  void onDownReleased( void );

  void networkAccepted( void );
  void networkRejected( void );

private:
  Ui::DialogNetworkCreate* ui;

  void swapRow( int x, int y );

  QStringList layerTypeList;
  QStringList activationTypeList;

  NeuralNetwork* network;

  std::map< QString, ActivationTypes > activationMap;
  std::map< QString, LayerTypes >      layerMap;

  bool newNetwork;
};

#endif  // DIALOG_NETWORK_CREATE_H

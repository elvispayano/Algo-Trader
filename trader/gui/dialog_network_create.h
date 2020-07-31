#ifndef DIALOG_NETWORK_CREATE_H
#define DIALOG_NETWORK_CREATE_H

#include <QDialog>

namespace Ui {
  class DialogNetworkCreate;
}

class DialogNetworkCreate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogNetworkCreate(QWidget *parent = nullptr);
  ~DialogNetworkCreate();

public slots:
  void onAddReleased(void);
  void onRemoveReleased(void);

private:
  Ui::DialogNetworkCreate *ui;
};

#endif // DIALOG_NETWORK_CREATE_H

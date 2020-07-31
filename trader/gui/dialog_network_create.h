#ifndef DIALOG_NETWORK_CREATE_H
#define DIALOG_NETWORK_CREATE_H

#include <QDialog>

namespace Ui {
  class DialogNetworkCreate;
}

class QTableWidgetItem;

class DialogNetworkCreate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogNetworkCreate(QWidget *parent = nullptr);
  ~DialogNetworkCreate();

public slots:
  void onAddReleased(void);
  void onRemoveReleased(void);
  void onUpReleased(void);
  void onDownReleased(void);

private:
  Ui::DialogNetworkCreate *ui;

  void getRow(QList<QTableWidgetItem*> &list, int row);
  void setRow(QList<QTableWidgetItem*>& list, int row);
};

#endif // DIALOG_NETWORK_CREATE_H

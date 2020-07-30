#ifndef DIALOG_POSTGRES_H
#define DIALOG_POSTGRES_H

// QT Includes
#include <QDialog>

// Forward Declaration
class Postgres;
class QPlainTextEdit;

namespace Ui {
  class DialogPostgres;
}

class DialogPostgres : public QDialog
{
  Q_OBJECT

public:
  explicit DialogPostgres(QWidget* parent = nullptr);
  ~DialogPostgres();

  bool isConnected(void) { return false; }
  Postgres* getDatabase() { return database; }

public slots:
  void connectReleased(void);
  void cancelReleased(void);
  
  void updateHost(void);
  void updatePort(void);
  void updateOptions(void);
  void updateTTY(void);
  void updateDatabase(void);
  void updateUsername(void);
  void updatePassword(void);
  
private:

  void highlight(QPlainTextEdit* obj, Qt::GlobalColor);

  Ui::DialogPostgres *ui;

  Postgres* database;
  std::string host;
  std::string port;
  std::string opt;
  std::string tty;
  std::string db;
  std::string user;
  std::string password;
};

#endif // DIALOG_POSTGRES_H

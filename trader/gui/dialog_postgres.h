#ifndef DIALOG_POSTGRES_H
#define DIALOG_POSTGRES_H

#include <QDialog>

namespace Ui {
class DialogPostgres;
}

class DialogPostgres : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPostgres(QWidget *parent = nullptr);
    ~DialogPostgres();

private:
    Ui::DialogPostgres *ui;
};

#endif // DIALOG_POSTGRES_H

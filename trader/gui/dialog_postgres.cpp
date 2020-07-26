#include "dialog_postgres.h"
#include "ui_dialog_postgres.h"

DialogPostgres::DialogPostgres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPostgres)
{
    ui->setupUi(this);
}

DialogPostgres::~DialogPostgres()
{
    delete ui;
}

#include "access_dialog.h"
#include "ui_access_dialog.h"

access_dialog::access_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::access_dialog)
{
    ui->setupUi(this);
}

access_dialog::~access_dialog()
{
    delete ui;
}

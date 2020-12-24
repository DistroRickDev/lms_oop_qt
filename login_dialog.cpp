#include "login_dialog.h"
#include "ui_login_dialog.h"

login_dialog::login_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_dialog)
{
    ui->setupUi(this);
}

login_dialog::~login_dialog()
{
    delete ui;
}

void login_dialog::on_goback_tn_clicked()
{

}

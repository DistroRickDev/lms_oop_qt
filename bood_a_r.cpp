#include "bood_a_r.h"
#include "ui_bood_a_r.h"

Bood_A_R::Bood_A_R(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bood_A_R)
{
    ui->setupUi(this);
}

Bood_A_R::~Bood_A_R()
{
    delete ui;
}

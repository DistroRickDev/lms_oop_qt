#include "warning_popup.h"
#include "ui_warning_popup.h"
#include <QDebug>

warning_popup::warning_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warning_popup)
{
    ui->setupUi(this);
}

warning_popup::~warning_popup()
{
    delete ui;
}

void warning_popup::setMessage(QString m)
{
    ui->warningMessageLabel->setText(m);
}


#include "bookselectionfilter.h"
#include "ui_bookselectionfilter.h"

BookSelectionFilter::BookSelectionFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookSelectionFilter)
{
    ui->setupUi(this);
}

BookSelectionFilter::~BookSelectionFilter()
{
    delete ui;
}

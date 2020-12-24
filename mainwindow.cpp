#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title
    this->setFixedSize(640, 480); //sets max window width to 600px height to 400px
    new_access->setFixedSize(640, 480); //sets max window width to 600px height to 400px
    new_access->show();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete new_access;
}







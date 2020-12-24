#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "access_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
     access_dialog *new_access = new (access_dialog) ;
private slots:

};
#endif // MAINWINDOW_H

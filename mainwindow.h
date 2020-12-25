#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include "access_dialog.h"
#include "library_data.h"


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

    //Add library books
     QMap<int, library_books> bMap;
     void print_map();
     void write_to_file();

private slots:
    void submit_btn_clicked();
};
#endif // MAINWINDOW_H

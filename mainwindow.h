#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QMap>
//#include <QVector>
#include <QDebug>
#include <QFile>
//#include <QTimer>
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

    // TYPE -> GENRE -> SUBGENRE
    QStringList bTypes;

    QStringList bGenres;  //other types
    QStringList bSubGenres; //other types

    //QStringList bSGenres; //type school
    //QStringList bSSubGenres; //type school

    //Map <-> IO functions
    void loadMap();
    void print_map();
    void write_to_file();

    //Build QStringLists
    void buildbTypes();

    void buildbGenres();
    void buildbSubGenres();

    void buildbSGenres();
    void buildbSSubGenres();

    //load combo box function
    void loadTypeComboBox();
    void loadFilterComboBox();


private slots:
    void submit_btn_clicked();
    void update_by_filter();
    void toggle_title_cb();
    void toggle_isbn_cb();
    void clear_lineEdit();
    void loadGenreComboBox();
    void loadSubGenreComboBox();
    void generateLibraryId();
};

#endif // MAINWINDOW_H

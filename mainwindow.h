#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include "library_data.h"
#include "bauxutils.h"


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
    QMap<unsigned long long, library_books> bMap;

    // TYPE -> GENRE -> SUBGENRE
    QStringList bTypes;

    QStringList bGenres;  //other types
    QStringList bSubGenres; //other types

    //QStringList bSGenres; //type school
    //QStringList bSSubGenres; //type school

    //failsafe
    unsigned long long ISBN_STORE;

    //Map <-> IO functions
    void loadMap();
    void print_map();
    void write_to_file();

    //Build QStringLists
    void buildbTypes();

    void buildbGenres();
    void buildbSubGenres();

    //load combo box function
    void loadTypeComboBox();
    void loadFilterComboBox();

    void loadTypeEditComboBox();

    void setConnections();
    void initFunctions();

    void clearEditCB();

    bool validateRegister(uint8_t opt);

    QString generateLibraryId();

    QString generateLibraryIDED();

    void populateTable();

    void generateError(QString);

private slots:
    void submit_btn_clicked();
    void update_by_filter();
    void toggle_title_cb();
    void toggle_isbn_entry();
    void clear_lineEdit();
    void loadGenreComboBox();
    void loadSubGenreComboBox();
    void enableEdit();
    void buildTitles();
    void buildInfoTable();
    void removeBook();
    void buildGenreEdit();
    void buildSubGenreEdit();
    void att_lid_reg();
    void att_lid_ed();
    void editBook();
    void tabChanged();
    void requestBook();
    void returnBook();
};

#endif // MAINWINDOW_H

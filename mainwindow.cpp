#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title

    //Connections
    connect(ui->submit_btn, &QPushButton::clicked, this, &MainWindow::submit_btn_clicked);
    connect(ui->clear_btn, &QPushButton::clicked, this, &MainWindow::clear_lineEdit);
    connect(ui->filter_btn, &QPushButton::clicked, this, &MainWindow::update_by_filter);
    connect(ui->title_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_title_cb);
    connect(ui->isbn_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_isbn_cb);
    connect(ui->id_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_id_cb);

    //Init Functions
    loadMap();
    print_map();
    loadComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMap()
{
    QFile books_file("books.txt");
    if(!books_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Invalid file";
    }

    QTextStream in(&books_file);

    while(!in.atEnd()){
        int id = 0;
        int num;
        bool av = true;
        id = in.readLine().toULong();
        QString t = in.readLine();
        QString a = in.readLine();
        QString g = in.readLine();
        int i = in.readLine().toULong();
        num = in.readLine().toULong();
        int avail = in.readLine().toInt();
        //qDebug() << "DEBUG AVAIL: " <<avail;
        if (avail == 0){
               av = false;
        }
        library_books new_book(a,i,g,t,id,num, av);
        bMap.insert(id, new_book);
        //qDebug() << "iterated";
    }
    books_file.close();
}

void MainWindow::submit_btn_clicked()
{
    loadMap();
    library_books new_book(ui->author_input->text(),
                           ui->isbn_input->text().toULong(),
                           ui->genre_input->text(),
                           ui->title_input->text(),
                           ui->id_input->text().toULong());

    bMap.insert(ui->id_input->text().toULong(), new_book);
    write_to_file();
    loadComboBox();
    print_map();
    clear_lineEdit();
}

void MainWindow::update_by_filter()
{
    for  (auto i : bMap) {
        if(ui->title_filter_rb->isChecked())
        {
            if(i.get_title() ==  ui->title_filter_cb->currentText()){
                ui->title_r_identifier->setText(i.get_title());
                ui->author_r_identifier->setText(i.get_author());
                ui->isbn_r_identifier->setText(QString::number(i.get_isbn()));
                ui->genre_r_identifier->setText(i.get_genre());
                ui->id_r_identifier->setText(QString::number(i.get_id()));
                break;
            }
        }
        else if(ui->isbn_filter_rb->isChecked()){
            if(QString::number(i.get_isbn()) ==  ui->isbn_filter_cb->currentText()){
                ui->title_r_identifier->setText(i.get_title());
                ui->author_r_identifier->setText(i.get_author());
                ui->isbn_r_identifier->setText(QString::number(i.get_isbn()));
                ui->genre_r_identifier->setText(i.get_genre());
                ui->id_r_identifier->setText(QString::number(i.get_id()));
                break;
            }
        }
        else if(ui->id_filter_rb->isChecked()){
            if(QString::number(i.get_id()) ==  ui->id_filter_cb->currentText()){
                ui->title_r_identifier->setText(i.get_title());
                ui->author_r_identifier->setText(i.get_author());
                ui->isbn_r_identifier->setText(QString::number(i.get_isbn()));
                ui->genre_r_identifier->setText(i.get_genre());
                ui->id_r_identifier->setText(QString::number(i.get_id()));
                break;
            }
        }
    }

}

void MainWindow::toggle_title_cb()
{
    if(ui->title_filter_rb->isChecked())
    {
        ui->title_filter_cb->setEnabled(true);
    }
    else{
        ui->title_filter_cb->setEnabled(false);
    }
}

void MainWindow::toggle_isbn_cb()
{
    if(ui->isbn_filter_rb->isChecked())
    {
        ui->isbn_filter_cb->setEnabled(true);
    }
    else{
        ui->isbn_filter_cb->setEnabled(false);
    }
}

void MainWindow::toggle_id_cb()
{
    if(ui->id_filter_rb->isChecked())
    {
        ui->id_filter_cb->setEnabled(true);
    }
    else{
        ui->id_filter_cb->setEnabled(false);
    }
}

void MainWindow::clear_lineEdit()
{
    ui->title_input->clear();
    ui->author_input->clear();
    ui->isbn_input->clear();
    ui->genre_input->clear();
    ui->id_input->clear();
}

void MainWindow::write_to_file()
{
    QFile book_io("books.txt");
    if(!book_io.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
    {
        qDebug()<< "Error Loading Data File\n";
    }
    QTextStream out(&book_io);
    //out << "The magic number is: " << 49 << "\n";
    for (auto it : bMap)
    {
        out << it.get_id()<< Qt::endl;
        out << it.get_title() << Qt::endl;
        out << it.get_author()<< Qt::endl;
        out << it.get_genre()<< Qt::endl;
        out << it.get_isbn()<< Qt::endl;
        out << it.get_number_of_copies() << Qt::endl;
        out << it.get_availability() << Qt::endl;
    }
    book_io.close();
    qDebug() << "FILE WRITTEN" << Qt::endl;
}

void MainWindow::loadComboBox()
{
    ui->title_filter_cb->clear();
    ui->isbn_filter_cb->clear();
    ui->id_filter_cb->clear();
    for(auto i : bMap)
    {
        ui->title_filter_cb->addItem(i.get_title());
        ui->isbn_filter_cb->addItem(QString::number(i.get_isbn()));
        ui->id_filter_cb->addItem(QString::number(i.get_id()));
    }
}


void MainWindow::print_map()
{
    for(auto it : bMap){
        qDebug() << "Title" << it.get_title();
        qDebug() << "Author:" << it.get_author();
        qDebug() << "ISBN:" << it.get_isbn();
        qDebug() << "Genre" << it.get_genre();
        qDebug() << "Book ID" << it.get_id();
        qDebug() << "Number of Copies" << it.get_number_of_copies();
        qDebug() << "Availability" << it.get_availability();
        //qDebug() << Qt::endl;
    }
}

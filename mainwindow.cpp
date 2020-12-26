#include "mainwindow.h"
#include "ui_mainwindow.h"

int bc = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title
    connect(ui->submit_btn, &QPushButton::clicked, this, &MainWindow::submit_btn_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submit_btn_clicked()
{
    library_books new_book(ui->author_input->text(), ui->isbn_input->text().toULong(), ui->genre_input->text(), ui->title_input->text(), random());
    bMap.insert(bc, new_book);
    bc ++;
    //print_map();
    write_to_file();
}

void MainWindow::write_to_file()
{
    QFile book_io("books.txt");
    if(!book_io.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<< "Error Loading Data File\n";
    }
    QTextStream out(&book_io);
    //out << "The magic number is: " << 49 << "\n";
    for (auto it : bMap)
    {
        out << it.get_title() << Qt::endl;
        out << it.get_author()<< Qt::endl;
        out << it.get_genre()<< Qt::endl;
        out << it.get_isbn()<< Qt::endl;
        out << it.get_id()<< Qt::endl;
    }
    book_io.close();
    qDebug() << "FILE WRITTEN" << Qt::endl;
}


void MainWindow::print_map()
{
    for(auto it : bMap){
        qDebug() << "Title" << it.get_title();
        qDebug() << "Author:" << it.get_author();
        qDebug() << "ISBN:" << it.get_isbn();
        qDebug() << "Genre" << it.get_genre();
        qDebug() << "Book ID" << it.get_id();
    }
}

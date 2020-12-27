#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title
    connect(ui->submit_btn, &QPushButton::clicked, this, &MainWindow::submit_btn_clicked);
    loadMap();
    print_map();
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
        id = in.readLine().toULong();
        QString t = in.readLine();
        QString a = in.readLine();
        QString g = in.readLine();
        int i = in.readLine().toULong();
        library_books new_book(a,i,g,t,id,1);
        bMap.insert(id, new_book);
        qDebug() << "iterated";
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
    print_map();
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
        qDebug() << Qt::endl;
    }
}

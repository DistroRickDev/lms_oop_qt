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

    connect(ui->type_cb,&QComboBox::textActivated, this, &MainWindow::loadGenreComboBox);
    connect(ui->genre_cb, &QComboBox::textActivated, this, &MainWindow::loadSubGenreComboBox);

    //Init Functions
    loadMap();
    print_map();
    loadFilterComboBox();
    loadTypeComboBox();
    loadGenreComboBox();
    //loadSubGenreComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildbTypes()
{
    QString booktypes[] = {"Books in Portuguese", "Books in Other Languages", "SchoolBooks"};
    for (int i= 0;i<3 ;i++ ) {
        bTypes.append(booktypes[i]);
    }
}

void MainWindow::buildbGenres()
{
    this->bGenres.clear();
    QStringList bGenre = {"Fiction", "Non Fiction"};
    QStringList bSchoolGenre = {"12th Grade","11th Grade","10th Grade","9th Grade","8th Grade","7th Grade",
                               "6th Grade","5th Grade","4th Grade","3rd Grade","2nd Grade","1st Grade"};
    if(ui->type_cb->currentText() == bTypes[0] || ui->type_cb->currentText() == bTypes[1])
    {
        this->bGenres = bGenre;
    }
    else{
        this->bGenres = bSchoolGenre;
    }
}

void MainWindow::buildbSubGenres()
{
    QStringList bSubGenre[2] = {
        {"Fairy Tails", "Fables"},
        {"Politics", "Health"}
    };
    QStringList bSchoolSubGenre = {"Mathematics", "Portuguese", "History", "Foreign Languages", "Philosophy"
                                  "Physics and Chemistry", "Natural Sciences"};
}

void MainWindow::buildbSGenres()
{

}

void MainWindow::buildbSSubGenres()
{

}

void MainWindow::loadTypeComboBox()
{
    buildbTypes();
    ui->type_cb->addItems(bTypes);
}

void MainWindow::loadGenreComboBox()
{
    ui->genre_cb->clear();
    buildbGenres();
    ui->genre_cb->addItems(bGenres);
}

void MainWindow::loadSubGenreComboBox()
{

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
        out << it.get_title() << Qt::endl;
        out << it.get_author()<< Qt::endl;
        out << it.get_type() << Qt::endl;
        out << it.get_genre()<< Qt::endl;
        out << it.get_subgenre() << Qt::endl;
        out << it.get_publisher() << Qt::endl;
        out << it.get_isbn()<< Qt::endl;
        out << it.get_edition_year() << Qt::endl;
        out << it.get_number_of_copies() << Qt::endl;
        out << it.get_availability() << Qt::endl;
        out << it.get_library_id() << Qt::endl;
    }
    book_io.close();
    qDebug() << "FILE WRITTEN" << Qt::endl;
}


void MainWindow::loadMap()
{
    QFile books_file("books.txt");
    if(!books_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Invalid file";
    }

    QTextStream in(&books_file);
    while(!in.atEnd()){


        bool av = true;
        QString tit = in.readLine();
        QString auth = in.readLine();
        QString typ = in.readLine();
        QString gen = in.readLine();
        QString subgen = in.readLine();
        QString pub = in.readLine();
        int is = in.readLine().toULong();
        int year = in.readLine().toInt();
        int num = in.readLine().toInt();
        int avail = in.readLine().toInt();
        //qDebug() << "DEBUG AVAIL: " <<avail;
        if (avail == 0){
            av = false;
        }
        QString libid = in.readLine();
        library_books new_book(tit,auth,typ, gen, subgen, pub, is, year, num, av, libid);
        bMap.insert(is, new_book);
    }
    books_file.close();
}

void MainWindow::submit_btn_clicked()
{
    loadMap();
    library_books new_book(
                ui->title_input->text(),
                ui->author_input->text(),
                ui->type_cb->currentText(),
                ui->genre_cb->currentText(),
                ui->subgenre_cb->currentText(),
                ui->publisher_input->text(),
                ui->isbn_input->text().toULong(),
                ui->edition_year_date->text().toInt(),
                ui->qty_sb->text().toInt(),
                true,
                ui->library_id_input->text());

    bMap.insert(ui->isbn_input->text().toULong(), new_book);
    write_to_file();
    loadFilterComboBox();
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
                break;
            }
        }
        else if(ui->isbn_filter_rb->isChecked()){
            if(QString::number(i.get_isbn()) ==  ui->isbn_filter_cb->currentText()){
                ui->title_r_identifier->setText(i.get_title());
                ui->author_r_identifier->setText(i.get_author());
                ui->isbn_r_identifier->setText(QString::number(i.get_isbn()));
                ui->genre_r_identifier->setText(i.get_genre());
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


void MainWindow::clear_lineEdit()
{
    ui->title_input->clear();
    ui->author_input->clear();
    ui->publisher_input->clear();
    ui->isbn_input->clear();
    ui->library_id_input->clear();
}


void MainWindow::loadFilterComboBox()
{
    ui->title_filter_cb->clear();
    ui->isbn_filter_cb->clear();
    for(auto i : bMap)
    {
        ui->title_filter_cb->addItem(i.get_title());
        ui->isbn_filter_cb->addItem(QString::number(i.get_isbn()));
    }
}


void MainWindow::generateLibraryId()
{

}


void MainWindow::print_map()
{
    for(auto it : bMap){
        qDebug() << "Title" << it.get_title();
        qDebug() << "Author:" << it.get_author();
        qDebug() << "Type:" << it.get_type();
        qDebug() << "Genre" << it.get_genre();
        qDebug() << "SubGenre" << it.get_subgenre();
        qDebug() << "Publisher:" << it.get_publisher();
        qDebug() << "ISBN:" << it.get_isbn();
        qDebug() << "Edition Year" << it.get_edition_year();
        qDebug() << "Library ID:" << it.get_library_id();
        qDebug() << "Number of Copies" << it.get_number_of_copies();
        qDebug() << "Availability" << it.get_availability();
        //qDebug() << Qt::endl;
    }
}



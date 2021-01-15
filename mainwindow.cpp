#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title
    this->setMaximumSize(1280, 720); //to avoid widget misplacement

    //Connections
    setConnections();

    //Init Functions
    initFunctions();
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
    this->bSubGenres.clear();
    QStringList bSubGenre[2] = {
        {				"Comics", "Fable", "Horror", "Adventure", "Myth", "Romance", "Novel", "Fiction", "Biography", "Drama", "Fictional" "History", "Westerns", "Poetry"
        },
        {				"Art", "Natural Sciences", "Social Sciences", "Leisure and Sport", "Self Empowerment", "Economics, Finances and Accounting",
                        "Engineering", "Health and well-Being", "Cuisine", "Maps and Tourist Guides", "History", "IT", "Medicine", "Politics", "Religion",
                        "Dictionaries and Encyclopedias"}
    };
    QStringList bSchoolSubGenre = {"Mathmatics", "Portuguese", "History and Geography", "Natural Sciences", "Physics and Chemestry", "Philosophy",
                                   "Foreign Languages", "Arts and Design", "Technology"};
    if(ui->genre_cb->currentText() == "Fiction")
    {
        this -> bSubGenres = bSubGenre[0];
    }
    else if(ui->genre_cb->currentText() == "Non Fiction"){
        this -> bSubGenres = bSubGenre[1];
    }
    else{
        this -> bSubGenres = bSchoolSubGenre;
    }
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
    loadSubGenreComboBox();
}

void MainWindow::loadSubGenreComboBox()
{
    ui->subgenre_cb->clear();
    buildbSubGenres();
    ui->subgenre_cb->addItems(bSubGenres);
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
    ui->type_edit->clear();
    ui->type_edit->addItems(bTypes);
    for  (auto it : bMap) {
        if(ui->title_filter_rb->isChecked())
        {
            if(it.get_title() == ui->title_filter_cb->currentText())
            {
                ui->title_edit->setText(it.get_title());
                ui->author_edit->setText(it.get_author());
                //int i = 0;
                // ui->type_edit->setCurrentText(it.get_type());
            }
        }
    }
}

void MainWindow::toggle_title_cb()
{
    if(ui->title_filter_rb->isChecked())
    {
        ui->title_filter_cb->setEnabled(true);
        ui->alphabet_cb->setEnabled(true);
    }
    else{
        ui->title_filter_cb->setEnabled(false);
        ui->alphabet_cb->setEnabled(false);
    }
}

void MainWindow::toggle_isbn_entry()
{
    if(ui->isbn_filter_rb->isChecked())
    {
        ui->isbn_filter_entry->setEnabled(true);
    }
    else{
        ui->isbn_filter_entry->setEnabled(false);
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
    ui->isbn_filter_entry->clear();
    ui->alphabet_cb->clear();

    bAuxUtils newAlphabet;

    ui->alphabet_cb->addItems(newAlphabet.return_alphabet());

}

void MainWindow::loadTypeEditComboBox()
{
    ui->type_edit->addItems(bTypes);
}


void MainWindow::generateLibraryId()
{
    srand(time(NULL));
    QString bID;
    QString t;
    if(ui->type_cb->currentText() == bTypes[0])
    {
        t = "PT";
    }
    else if(ui->type_cb->currentText() == bTypes[1])
    {
        t = "OL";
    }
    else{
        t = "S";
    }
    QChar g = ui->genre_cb->currentText().at(0);
    QChar s = ui->subgenre_cb->currentText().at(0);
    QString shelf = QString::number(rand() % 30);
    QString pos = QString::number(rand() % 30);
    bID.append(t), bID.append(g),bID.append(s), bID.append(shelf), bID.append(pos);
    ui->library_id_input->setText(bID);
}

void MainWindow::enableEdit()
{
    if(ui->editable_check->isChecked())
    {
        //qDebug() << "YOU CAN EDIT NOW";
        ui->remove_btn->setEnabled(false); //disables remove option
        ui->edit_btn->setEnabled(true); // enables edit option
        ui->title_edit->setEnabled(true); //enables text line edit
        ui->author_edit->setEnabled(true); //enables author line edit
        ui->type_edit->setEnabled(true); //enables type line edit
        ui->genre_edit->setEnabled(true); //enables genre line edit
        ui->subgenre_edit->setEnabled(true); //enables subgenre line edit
        ui->publisher_edit->setEnabled(true); //enables publisher line edit
        ui->year_edit->setEnabled(true); //enables EY line edit
        ui->isbn_edit->setEnabled(true); //enables isbn line edit
        ui->qty_edit->setEnabled(true); //enables qty edit
    }
    else {
        ui->remove_btn->setEnabled(true); //enables remove option
        ui->edit_btn->setEnabled(false); // disables edit option
        ui->title_edit->setEnabled(false); //disables text line edit
        ui->author_edit->setEnabled(false); //disables author line edit
        ui->type_edit->setEnabled(false); //disables type line edit
        ui->genre_edit->setEnabled(false); //disables genre line edit
        ui->subgenre_edit->setEnabled(false); //disables subgenre line edit
        ui->publisher_edit->setEnabled(false); //disables publisher line edit
        ui->year_edit->setEnabled(false); //disables EY line edit
        ui->isbn_edit->setEnabled(false); //disables isbn line edit
        ui->qty_edit->setEnabled(false); //disables qty edit
    }
}

void MainWindow::buildTitles()
{
    ui->title_filter_cb->clear();
    for(auto it: bMap)
    {
        if(it.get_title().contains(ui->alphabet_cb->currentText().at(0)))
        {
            //qDebug()<< "TEXT EXISTS";
            ui->title_filter_cb->addItem(it.get_title());
        }
    }
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


void MainWindow:: setConnections()
{
    connect(ui->submit_btn, &QPushButton::clicked, this, &MainWindow::submit_btn_clicked);
    connect(ui->clear_btn, &QPushButton::clicked, this, &MainWindow::clear_lineEdit);
    connect(ui->filter_btn, &QPushButton::clicked, this, &MainWindow::update_by_filter);
    connect(ui->title_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_title_cb);
    connect(ui->isbn_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_isbn_entry);
    //connect(ui->title_filter_cb, &QComboBox::textActivated, this, );

    connect(ui->type_cb,&QComboBox::textActivated, this, &MainWindow::loadGenreComboBox);
    connect(ui->type_cb,&QComboBox::textActivated, this, &MainWindow::generateLibraryId);
    connect(ui->genre_cb, &QComboBox::textActivated, this, &MainWindow::loadSubGenreComboBox);
    connect(ui->genre_cb,&QComboBox::textActivated, this, &MainWindow::generateLibraryId);
    connect(ui->subgenre_cb,&QComboBox::textActivated, this, &MainWindow::generateLibraryId);
    connect(ui->editable_check, &QCheckBox::toggled, this, &MainWindow::enableEdit);
    connect(ui->alphabet_cb, &QComboBox::textActivated, this, &MainWindow::buildTitles);
}

void MainWindow:: initFunctions()
{
    loadMap();
    print_map();
    loadFilterComboBox();
    loadTypeComboBox();
    loadGenreComboBox();
    loadSubGenreComboBox();
    generateLibraryId();
    enableEdit();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "warning_popup.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Management System"); //Sets main window title
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
        out << it.get_number_of_current_books() << Qt::endl;
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
        unsigned long long is = in.readLine().toULongLong();
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
    if(validateRegister(0)){library_books new_book(
                    ui->title_input->text(),
                    ui->author_input->text(),
                    ui->type_cb->currentText(),
                    ui->genre_cb->currentText(),
                    ui->subgenre_cb->currentText(),
                    ui->publisher_input->text(),
                    ui->isbn_input->text().toULongLong(),
                    ui->edition_year_date->text().toInt(),
                    ui->qty_sb->text().toInt(),
                    true,
                    ui->library_id_input->text());

        bMap.insert(ui->isbn_input->text().toULongLong(), new_book);
        write_to_file();
        loadFilterComboBox();
        print_map();
        clear_lineEdit();
    }
}

void MainWindow::update_by_filter()
{
    ui->type_edit->clear();
    ui->type_edit->addItems(bTypes);
    buildGenreEdit();
    for  (auto it : bMap) {
        if(ui->title_filter_rb->isChecked())
        {
            if(it.get_title() == ui->title_filter_cb->currentText())
            {
                ui->title_edit->setText(it.get_title());
                ui->author_edit->setText(it.get_author());
                ui->isbn_edit->setText(QString::number(it.get_isbn()));
                ISBN_STORE = it.get_isbn();
                ui->publisher_edit->setText(it.get_publisher());
                ui->lid_edit->setText(it.get_library_id());
                ui->year_edit->setDate(QDate(it.get_edition_year(), 1, 1));
                ui->qty_edit->setValue(it.get_number_of_current_books());
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


QString MainWindow::generateLibraryId()
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
    return bID;
}

QString MainWindow::generateLibraryIDED()
{
    srand(time(NULL));
    QString bID;
    QString t;
    if(ui->type_edit->currentText() == bTypes[0])
    {
        t = "PT";
    }
    else if(ui->type_edit->currentText() == bTypes[1])
    {
        t = "OL";
    }
    else{
        t = "S";
    }
    QChar g = ui->genre_edit->currentText().at(0);
    QChar s = ui->subgenre_edit->currentText().at(0);
    QString shelf = QString::number(rand() % 30);
    QString pos = QString::number(rand() % 30);
    bID.append(t), bID.append(g),bID.append(s), bID.append(shelf), bID.append(pos);
    return bID;
}

void MainWindow::populateTable()
{
    ui->reqTable->clearContents();
    ui->reqTable->setColumnCount(5);
    QStringList labels{"ISBN" , "TITLE" ,"AUTHOR" , "COPIES AVAILABLE" , "AVAILABILITY"};
    ui->reqTable->setHorizontalHeaderLabels(labels);
    loadMap();
    ui->reqTable->setRowCount(bMap.size());
    int col = 0;
    for(auto it : bMap)
    {
        ui->reqTable->setItem(col, 0, new QTableWidgetItem(QString::number(it.get_isbn())));
        ui->reqTable->setItem(col, 1, new QTableWidgetItem(it.get_title()));
        ui->reqTable->setItem(col, 2, new QTableWidgetItem(it.get_author()));
        ui->reqTable->setItem(col, 3, new QTableWidgetItem(QString::number(it.get_number_of_current_books())));
        ui->reqTable->setItem(col, 4, new QTableWidgetItem(QString::number(it.get_availability())));
        col++;
    }
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
        if(it.get_title().at(0) == ui->alphabet_cb->currentText().at(0) || it.get_title().at(0) == (ui->alphabet_cb->currentText().at(0).toLatin1()) + 32)
        {
            //qDebug()<< "TEXT EXISTS";
            ui->title_filter_cb->addItem(it.get_title());
        }
    }
}

void MainWindow::buildInfoTable()
{
    ui->infoTable->clearContents();
    ui->infoTable->setColumnCount(10);
    QStringList labels{"ISBN" , "TITLE" ,"AUTHOR" , "TYPE", "GENRE", "SUBGENRE", "PUBLISHER", "YEAR OF EDITION", "LIB_ID" ,"AVAILABILITY" };
    ui->infoTable->setHorizontalHeaderLabels(labels);
    loadMap();
    ui->infoTable->setRowCount(bMap.size());
    int row = 0;
    for(auto it : bMap)
    {
        ui->infoTable->setItem(row, 0, new QTableWidgetItem(QString::number(it.get_isbn())));
        qDebug()<< it.get_isbn();
        ui->infoTable->setItem(row, 1, new QTableWidgetItem(it.get_title()));
        ui->infoTable->setItem(row, 2, new QTableWidgetItem(it.get_author()));
        ui->infoTable->setItem(row, 3, new QTableWidgetItem(it.get_type()));
        ui->infoTable->setItem(row, 4, new QTableWidgetItem(it.get_genre()));
        ui->infoTable->setItem(row, 5, new QTableWidgetItem(it.get_subgenre()));
        ui->infoTable->setItem(row, 6, new QTableWidgetItem(it.get_publisher()));
        ui->infoTable->setItem(row, 7, new QTableWidgetItem(QString::number(it.get_edition_year())));
        ui->infoTable->setItem(row, 8, new QTableWidgetItem(it.get_library_id()));
        ui->infoTable->setItem(row, 9, new QTableWidgetItem(QString::number(it.get_availability())));
        row++;
    }
}

void MainWindow::removeBook()
{
    loadMap();
    auto it=bMap.find(ui->isbn_edit->text().toULongLong());
    bMap.erase (it);
    print_map();
    clearEditCB();
    write_to_file();
}

void MainWindow::buildGenreEdit()
{
    ui->genre_edit->clear();
    this->bGenres.clear();
    QStringList bGenre = {"Fiction", "Non Fiction"};
    QStringList bSchoolGenre = {"12th Grade","11th Grade","10th Grade","9th Grade","8th Grade","7th Grade",
                                "6th Grade","5th Grade","4th Grade","3rd Grade","2nd Grade","1st Grade"};
    if(ui->type_edit->currentText() == bTypes[0] || ui->type_edit->currentText() == bTypes[1])
    {
        this->bGenres = bGenre;
    }
    else{
        this->bGenres = bSchoolGenre;
    }
    ui->genre_edit->addItems(bGenres);

    buildSubGenreEdit();
}

void MainWindow::buildSubGenreEdit()
{
    ui->subgenre_edit->clear();
    this->bSubGenres.clear();
    QStringList bSubGenre[2] = {
        {
            "Comics", "Fable", "Horror", "Adventure", "Myth", "Romance", "Novel", "Fiction", "Biography", "Drama", "Fictional" "History", "Westerns", "Poetry"
        },
        {
            "Art", "Natural Sciences", "Social Sciences", "Leisure and Sport", "Self Empowerment", "Economics, Finances and Accounting",
            "Engineering", "Health and well-Being", "Cuisine", "Maps and Tourist Guides", "History", "IT", "Medicine", "Politics", "Religion",
            "Dictionaries and Encyclopedias"
        }
    };
    QStringList bSchoolSubGenre = {
        "Mathmatics", "Portuguese", "History and Geography", "Natural Sciences", "Physics and Chemestry", "Philosophy",
        "Foreign Languages", "Arts and Design", "Technology"};
    if(ui->genre_edit->currentText() == "Fiction")
    {
        this -> bSubGenres = bSubGenre[0];
    }
    else if(ui->genre_edit->currentText() == "Non Fiction"){
        this -> bSubGenres = bSubGenre[1];
    }
    else{
        this -> bSubGenres = bSchoolSubGenre;
    }
    ui->subgenre_edit->addItems(bSubGenres);
}

void MainWindow::att_lid_reg()
{
    ui->library_id_input->setText(generateLibraryId());
}

void MainWindow::att_lid_ed()
{
    ui->lid_edit->setText(generateLibraryIDED());
}

void MainWindow::editBook()
{
    loadMap();
    auto it=bMap.find(ISBN_STORE);
    bMap.erase(it);
    if(validateRegister(1)){
        library_books new_book(
                    ui->title_edit->text(),
                    ui->author_edit->text(),
                    ui->type_edit->currentText(),
                    ui->genre_edit->currentText(),
                    ui->subgenre_edit->currentText(),
                    ui->publisher_edit->text(),
                    ui->isbn_edit->text().toULongLong(),
                    ui->year_edit->text().toInt(),
                    ui->qty_edit->text().toInt(),
                    true,
                    ui->lid_edit->text());

        bMap.insert(ui->isbn_edit->text().toULongLong(), new_book);
        write_to_file();
        print_map();
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
        qDebug() << "Number of Copies" << it.get_number_of_current_books();
        qDebug() << "Availability" << it.get_availability();
        //qDebug() << Qt::endl;
    }
}

void MainWindow::tabChanged( )
{
    int index = ui->MainWindowTab->currentIndex();
    //qDebug() << "Reached tab" << index << Qt::endl;
    if(index == 0)
    {
        buildInfoTable();
    }
    else if(index == 2)
    {
        populateTable();
    }
    else{
    }
}

void MainWindow::requestBook()
{
  if(ui->reqTable->currentColumn() == 0){
    qDebug() <<"Current selected item is: "<< ui->reqTable->currentItem()->text();
    auto it = bMap.find(ui->reqTable->currentItem()->text().toULongLong());
    it->decrement_number();
    bMap.insert(it.key(), it.value());
  }
  else{
   //qDebug() <<"Please select the ISBN columsn";
  generateError("PLEASE SELECT AN ISBN ITEM");
  }
    write_to_file();
    populateTable();
 }

void MainWindow::returnBook()
{

}


void MainWindow:: setConnections()
{
    connect(ui->submit_btn, &QPushButton::clicked, this, &MainWindow::submit_btn_clicked);
    connect(ui->clear_btn, &QPushButton::clicked, this, &MainWindow::clear_lineEdit);
    connect(ui->filter_btn, &QPushButton::clicked, this, &MainWindow::update_by_filter);
    connect(ui->title_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_title_cb);
    connect(ui->isbn_filter_rb, &QPushButton::toggled, this, &MainWindow::toggle_isbn_entry);


    connect(ui->type_cb,&QComboBox::textActivated, this, &MainWindow::loadGenreComboBox);
    connect(ui->type_cb,&QComboBox::textActivated, this, &MainWindow::att_lid_reg);
    connect(ui->genre_cb, &QComboBox::textActivated, this, &MainWindow::loadSubGenreComboBox);
    connect(ui->genre_cb,&QComboBox::textActivated, this, &MainWindow::att_lid_reg);
    connect(ui->subgenre_cb,&QComboBox::textActivated, this, &MainWindow::att_lid_reg);
    connect(ui->editable_check, &QCheckBox::toggled, this, &MainWindow::enableEdit);
    connect(ui->alphabet_cb, &QComboBox::textActivated, this, &MainWindow::buildTitles);
    connect(ui->remove_btn, &QPushButton::clicked, this, &MainWindow::removeBook);

    connect(ui->type_edit, &QComboBox::textActivated, this, &MainWindow::buildGenreEdit);
    connect(ui->genre_edit, &QComboBox::textActivated, this, &MainWindow::buildSubGenreEdit);

    connect(ui->type_edit, &QComboBox::textActivated, this, &MainWindow::att_lid_ed);
    connect(ui->genre_edit, &QComboBox::textActivated, this, &MainWindow::att_lid_ed);
    connect(ui->subgenre_edit, &QComboBox::textActivated, this, &MainWindow::att_lid_ed);

    connect(ui->edit_btn, &QPushButton::clicked, this, &MainWindow::editBook);
    connect(ui->MainWindowTab, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    connect(ui->reqBookBtn, &QPushButton::clicked, this, &MainWindow::requestBook);
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

    //test
    buildInfoTable();
    populateTable();
}

void MainWindow::clearEditCB()
{
    loadFilterComboBox();
    ui->author_edit->clear();
    ui->title_edit->clear();
    ui->type_edit->clear();
    ui->subgenre_edit->clear();
    ui->genre_edit->clear();
    ui->publisher_edit->clear();
    ui->year_edit->setDate(QDate(2000,1,1));
    ui->isbn_edit->clear();
    ui->qty_edit->setValue(0);
    ui->lid_edit->clear();
}

bool MainWindow::validateRegister(uint8_t opt)
{
    if (opt == 0)
    {
        for (int i = 0 ;i <127 ;i++ ) {
            if((i >= 0 && i <= 47) || (i >= 58 && i <= 64) || (i >= 91 && i <= 96) || i >= 123)
            {
                if(ui->title_input->text().at(0) == i)
                {
                    qDebug() <<"TITLE FIRST CHAR IS INVALID";
                    generateError("TITLE FIRST CHAR IS INVALID");
                    return false;
                }
                else{
                    continue;
                }
            }
        }
        if(ui->isbn_input->text().length()!=13)
        {
            qDebug() << "ISBN DIFFERENT THAN 13 DIGITS";
            generateError("ISBN DIFFERENT THAN 13 DIGITS");
            return false;
        }
        for(auto it: bMap)
        {
            if(it.get_isbn() == ui->isbn_input->text().toULongLong())
            {
                qDebug()<< "ISBN ALREADY REGISTERED";
                generateError("ISBN ALREADY REGISTERED");
                return false;
            }
        }
        return true;
    }
    else{
        for (int i = 0; i <127 ;i++ ) {
            if((i >= 0 && i <= 47) || (i >= 58 && i <= 64) || (i >= 91 && i <= 96) || i >= 123)
            {
                if(ui->title_edit->text().at(0) == i)
                {
                    qDebug() <<"TITLE FIRTS CHAR IS INVALID";
                    generateError("TITLE FIRST CHAR IS INVALID");
                    return false;
                }
                else{
                    continue;
                }
            }
        }
        if(ui->isbn_edit->text().length()!=13)
        {
            qDebug() << "ISBN DIFFERENT THAN 13 DIGITS\n";
            generateError("ISBN DIFFERENT THAN 13 DIGITS");
            return false;
        }
        for(auto it: bMap)
        {
            if(it.get_isbn() == ui->isbn_input->text().toULongLong() && ui->isbn_input->text().toULongLong() != ISBN_STORE)
            {
                qDebug()<< "ISBN ALREADY REGISTERED";
                generateError("ISBN ALREADY REGISTERED");
                return false;
            }
        }
    }
    return true;
}

void MainWindow::generateError(QString err)
{
   warning_popup error;
   error.setModal(true);
   error.setMessage(err);
   error.exec();
}


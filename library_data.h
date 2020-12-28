#ifndef LIBRARY_DATA_H
#define LIBRARY_DATA_H

#include "book.h"

class library_books: protected Book
{
protected:
    bool availability; //if true is available else is not available
    int number_of_copies;
    QString library_id;
    QString sub_genre;
public:
    library_books(QString a, uint64_t i, QString g, QString t, QString e, int y, int num_c = 1, bool availability = true, QString li="N/A", QString sg ="N/A"):Book (a, i, g, t, e, y){
        this->availability = availability;
        number_of_copies = num_c;
        library_id = li;
        sub_genre = sg;
    }
    //~library_books();

    QString get_author();
    uint64_t get_isbn();
    QString get_genre();
    QString get_title();
    QString get_subgenre();
    QString get_library_id();
    QString get_publisher();
    bool get_availability();
    int get_number_of_copies();
    int get_edition_year();
};


/*
    QString title;
    QString author;
    QString genre;
    uint64_t isbn;
    QString editor;
    int year_of_edition;
    Book(QString author = "N/A", uint64_t isbn = 000000000, QString genre = "N/A", QString title = "UNTITLED", QString editor="N/A", int yoe = 2000);
*/

#endif // LIBRARY_DATA_H

#ifndef LIBRARY_DATA_H
#define LIBRARY_DATA_H

#include "book.h"

class library_books: protected Book
{
protected:
    bool availability; //if true is available else is not available
    int number_of_copies;
    QString library_id;
public:
    library_books(QString title, QString author,QString type, QString genre, QString subgenre,QString publisher, uint64_t isbn, int year,
                  int num_c = 1, bool availability = true, QString li="N/A"):Book (title, author, type, genre, subgenre, publisher,isbn, year){
        this->availability = availability;
        number_of_copies = num_c;
        library_id = li;
    }
    //~library_books();

    QString get_author();
    uint64_t get_isbn();
    QString get_type();
    QString get_genre();
    QString get_title();
    QString get_subgenre();
    QString get_library_id();
    QString get_publisher();
    bool get_availability();
    int get_number_of_copies();
    int get_edition_year();

    //generate library id
    void add_library_id();
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

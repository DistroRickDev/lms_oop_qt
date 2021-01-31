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
    library_books(QString title, QString author,QString type, QString genre, QString subgenre,QString publisher, unsigned long long isbn, int year,
                  int num_c = 1, bool availability = true, QString li="N/A"):Book (title, author, type, genre, subgenre, publisher,isbn, year){
        this->availability = availability;
        number_of_copies = num_c;
        library_id = li;
    }
    //~library_books();

    QString get_author();
    unsigned long long get_isbn();
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

#endif // LIBRARY_DATA_H

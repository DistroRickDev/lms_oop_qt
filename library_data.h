#ifndef LIBRARY_DATA_H
#define LIBRARY_DATA_H

#include "book.h"
#include <QDate>

class library_books: protected Book
{
protected:
    bool availability; //if true is available else is not available
    int number_of_copies;
    QString library_id;
    int number_of_current_books;
    QDate request_date;
    QDate return_date;
public:
    library_books(QString title, QString author,QString type, QString genre, QString subgenre,QString publisher, unsigned long long isbn, int year,
                  int num_c = 1, bool availability = true, QString li="N/A", QDate req = QDate(), QDate ret = QDate()):Book (title, author, type, genre, subgenre, publisher,isbn, year){
        this->availability = availability;
        number_of_copies = num_c;
        library_id = li;
        request_date = req;
        return_date = ret;
        number_of_current_books = number_of_copies;
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
    int get_number_of_current_books();
    int get_edition_year();
    //generate library id
    void add_library_id();
    void setAvaialbility(bool);
    void increment_number();
    void decrement_number();
    void set_request_date(QDate);
    void set_return_date(QDate);
};

#endif // LIBRARY_DATA_H

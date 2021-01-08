#ifndef BOOK_H
#define BOOK_H

#include<QString>

class Book
{

protected:
    QString title;
    QString author;
    QString type;
    QString genre;
    QString sub_genre;
    QString publisher;
    int edition_year;
    uint64_t isbn;
    double library_id;


public:
    Book(QString author = "N/A", uint64_t isbn = 000000000, QString genre = "N/A", QString title = "UNTITLED", QString publisher="N/A", int yoe = 2000);

   // ~Book();
};

#endif // BOOK_H

#ifndef BOOK_H
#define BOOK_H

#include<QString>

class Book
{

protected:
    QString title;
    QString author;
    QString genre;
    uint64_t isbn;
    QString publisher;
    int edition_year;

public:
    Book(QString author = "N/A", uint64_t isbn = 000000000, QString genre = "N/A", QString title = "UNTITLED", QString publisher="N/A", int yoe = 2000);

   // ~Book();
};

#endif // BOOK_H

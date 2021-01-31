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
    unsigned long long  isbn;

public:
    Book(QString title = "UNTITLED", QString author = "N/A", QString type = "N/A", QString genre = "N/A", QString sub_genre = "N/A", QString publisher="N/A", unsigned long long  isbn = 0000000000000, int yoe = 2000);

   // ~Book();
};

#endif // BOOK_H

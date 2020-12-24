#ifndef BOOK_H
#define BOOK_H

#include<QString>

class Book
{

protected:
     QString author;
     uint64_t isbn;
     QString genre;
     QString title;
public:
    Book(QString author = "N/A", uint64_t isbn = 000000000, QString genre = "N/A", QString title = "UNTITLED");
};

#endif // BOOK_H

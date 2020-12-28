#include "book.h"

Book::Book(QString author, uint64_t isbn, QString genre, QString title, QString publisher, int yoe)
{
    //Book(QString author = "N/A", uint64_t isbn = 000000000, QString genre = "N/A", QString title = "UNTITLED", QString editor="N/A", int yoe = 2000);
    this->author = author;
    this->isbn = isbn;
    this->genre = genre;
    this->title = title;
    this->publisher = publisher;
    this->edition_year = yoe;
}

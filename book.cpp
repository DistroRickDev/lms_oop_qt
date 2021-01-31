#include "book.h"

Book:: Book(QString title, QString author, QString type, QString genre, QString sub_genre, QString publisher, unsigned long long  isbn , int yoe)
{
    this->title = title;
    this->author = author;
    this->type = type;
    this->genre = genre;
    this->sub_genre = sub_genre;
    this->publisher = publisher;
    this->isbn = isbn;
    this->edition_year = yoe;
}

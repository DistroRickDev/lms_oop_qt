#include "book.h"

Book::Book(QString author, uint64_t isbn, QString genre, QString title)
{
    this->author = author;
    this->isbn = isbn;
    this->genre = genre;
    this->title = title;
}

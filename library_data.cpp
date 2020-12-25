#include "library_data.h"

QString library_books::get_author()
{
    return author;
}

uint64_t library_books::get_isbn()
{
    return isbn;
}

QString library_books::get_genre()
{
    return genre;
}

QString library_books::get_title()
{
    return title;
}

int library_books::get_id()
{
    return book_id;
}

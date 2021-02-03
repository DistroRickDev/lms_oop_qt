#include "library_data.h"

QString library_books::get_author()
{
    return author;
}

unsigned long long int library_books::get_isbn()
{
    return isbn;
}

QString library_books::get_type()
{
    return type;
}

QString library_books::get_genre()
{
    return genre;
}

QString library_books::get_title()
{
    return title;
}

QString library_books::get_subgenre()
{
    return sub_genre;
}

QString library_books::get_library_id()
{
    return library_id;
}

QString library_books::get_publisher()
{
    return publisher;
}

bool library_books::get_availability()
{
    return availability;
}

int library_books::get_number_of_current_books()
{
    return number_of_current_books;
}

int library_books::get_edition_year()
{
    return edition_year;
}

void library_books::setAvaialbility(bool avail)
{
    this->availability = avail;
}

void library_books::increment_number()
{
    number_of_current_books+=1;
}

void library_books::decrement_number()
{
    number_of_current_books-=1;
}

void library_books::set_request_date(QDate date)
{
    request_date = date;
}

void library_books::set_return_date(QDate date)
{
    return_date = date;
}


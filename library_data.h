#ifndef LIBRARY_DATA_H
#define LIBRARY_DATA_H

#include "book.h"

class library_books: protected Book
{
protected:
    int book_id;
    bool availability; //if true is available else is not available
    int number_of_copies;
public:
    library_books(QString a, uint64_t i, QString g, QString t, int id, int num_c = 1, bool availability = true):Book (a, i, g, t){
        this->book_id = id;
        this->availability = availability;
        number_of_copies = num_c;
    }
    QString get_author();
    uint64_t get_isbn();
    QString get_genre();
    QString get_title();
    bool get_availability();
    int get_number_of_copies();
    int get_id();
};

class library_roles
{
protected:
    bool can_register;
    int level_of_access;
    QString role;
    int member_number;
    static int library_members_counter;
public:
       library_roles(bool, int, QString);
};

class library_members: library_roles {
    QString name;
    int age;
};

#endif // LIBRARY_DATA_H

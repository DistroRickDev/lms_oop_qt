#ifndef LIBRARY_DATA_H
#define LIBRARY_DATA_H

#include "book.h"

class library_books: protected Book
{
private:
    int book_id;
public:
    library_books(QString a, uint64_t i, QString g, QString t, int id):Book (a, i, g, t){
        this->book_id = id;
    }

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

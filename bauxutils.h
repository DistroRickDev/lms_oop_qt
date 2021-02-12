#ifndef BAUXUTILS_H
#define BAUXUTILS_H

#include <QList>
#include <QDate>


class bAuxUtils
{
    QStringList bAlphabet;
public:

    bAuxUtils();
    void buildBAlphabet();
    QStringList return_alphabet();
    static bool validateReqDate(QDate, QDate);
};

#endif // BAUXUTILS_H

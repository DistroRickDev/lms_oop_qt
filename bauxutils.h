#ifndef BAUXUTILS_H
#define BAUXUTILS_H

#include <QList>



class bAuxUtils
{
    QStringList bAlphabet;
public:

    bAuxUtils();
    void buildBAlphabet();
    QStringList return_alphabet();
};

#endif // BAUXUTILS_H

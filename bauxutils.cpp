#include "bauxutils.h"

bAuxUtils::bAuxUtils()
{
    buildBAlphabet();
}

void bAuxUtils::buildBAlphabet()
{
    for(int i=65; i<=90;i++){
        bAlphabet.append(QString((char) i));
    }
}

QStringList bAuxUtils::return_alphabet()
{
    return bAlphabet;
}

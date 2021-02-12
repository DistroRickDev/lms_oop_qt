#include "bauxutils.h"

bAuxUtils::bAuxUtils()
{
    buildBAlphabet();
}

void bAuxUtils::buildBAlphabet()
{
    for(int i=48; i<=90;i++){
        if(i >=58 && i <= 64)
        {
            continue;
        }
        else{
            bAlphabet.append(QString((char) i));
        }
      }

}

QStringList bAuxUtils::return_alphabet()
{
    return bAlphabet;
}

bool bAuxUtils::validateReqDate(QDate req, QDate ret)
{
    if(ret < QDate::currentDate() || req < QDate::currentDate())
    {
        return false;
    }
    if (ret < req)
    {
        return false;
    }
    if(ret.toJulianDay() - req.toJulianDay() > 12)
    {
        return false;
    }
    else{
        return true;
    }
}

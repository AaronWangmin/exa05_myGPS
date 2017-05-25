#include "gstring.h"

GString::GString(const QString &str):gstring(str)
{

}

double GString::str2num(int pos,int npos) const
{
    QString temp = gstring.mid(pos,npos);
    return temp.toDouble();
}


#include "gtime.h"

GTime::GTime():second(0)
{

}

GTime::GTime(double d):second(d)
{

}

void GTime::fromString(const QString &source, int pos)
{
    second = str2time(source,pos);
}

double GTime::getSecond() const
{
    return second;
}

double GTime::str2time(const QString &source, int pos) const
{
    QString temp = source.mid(0,pos);
    QDateTime qtime = QDateTime::fromString(temp,"yy M d h m s");
    qtime.setTimeSpec(Qt::UTC);
    double second_int = qtime.toTime_t();

    temp = source.mid(pos);
    double second_decimal = temp.toDouble();

    return second_int + second_decimal;
}

double GTime::gtime2second(int week, double sec) const
{
    double added =  str2time(gps0,17);
    return week *7*86400 + sec + added;
}

#ifndef GTIME_H
#define GTIME_H

#include <QDateTime>

#include "gpshead.h"

class GTime : public QDateTime
{
public:   

    GTime();
    GTime(double d);

    /**
     * @brief fromString
     * @param source       QString     I   string ("yy mm dd hh mm ss.sss")
     * @param pos          int         I   position of the fraction of second(eg:17)
     * @return             double      O
     */
    void fromString(const QString& source,int pos);

    double getSecond() const;                              // get seconds from 1970 01 01 00:00:00
    double gtime2second(int week,double sec) const;        // get GPS time.


private:
    double second;      // seconds from 1970 01 01 00:00:00.00
    /**
     * @brief str2time
     * @param source       QString     I   string ("yy mm dd hh mm ss.sss")
     * @param pos          int         I   position of the fraction of second(eg:17)
     * @return             double      O
     */
    double str2time(const QString& source,int pos) const;  // seconds from 1970 01 01 00:00:00


};

#endif // GTIME_H

#include "rinex3x.h"

#include <QFile>
#include <QDebug>

#include <string>
#include <iostream>
using namespace std;

Rinex3x::Rinex3x()
{

}

void Rinex3x::readRinex3(const QString& fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Not found file! " << endl;
        return;
    }

    QByteArray line;
    string strTemp;
    while (!file.atEnd()) {
        line = file.readLine();
        strTemp = line.toStdString();

        if( strTemp.find("END OF HEADER") != string::npos)  // skip the header of rinex
            break;
    }

    while(!file.atEnd()){
        vector<string> strEphRecord;        // extract one ephemeris record from 8 lines.
        for(int i = 0; i < 8; i++){
            line = file.readLine();
            strTemp = line.toStdString();
            strEphRecord.push_back(strTemp);
        }

        eph_t eph;
        parseEphRecord(eph,strEphRecord);   // parse one ephemeris data record.

        ephData.push_back(eph);
    }
    file.close();
}

void Rinex3x::parseEphRecord(eph_t& eph,const vector<string> &str) const
{
    // the 1th line of ephemeris record.
    string temp = str.at(0);
    eph.sat                = std::stoi( temp.substr(0,2));

    GTime gtime;
    gtime.fromString(QString::fromStdString(temp.substr(3,19)),17);
    eph.toc = gtime.getSecond();

//    tm tocCalendar;
//    int tempToc            = std::stoi( temp.substr(3,2));
//    tocCalendar.tm_year    = tempToc + 100;
//    tocCalendar.tm_mon     = std::stoi( temp.substr(6,2)) - 1;
//    tocCalendar.tm_mday    = std::stoi( temp.substr(9,2));
//    tocCalendar.tm_hour    = std::stoi( temp.substr(12,2));
//    tocCalendar.tm_min     = std::stoi( temp.substr(15,2));
//    tocCalendar.tm_sec     = std::stoi( temp.substr(18,2));
//    eph.toc.time           = mktime(&tocCalendar);     // times since 1970 01 01 00:00:00
////    cout << asctime(&tocCalendar) << endl << eph.toc.time << endl;

//    eph.toc.sec             = std::stod( temp.substr(20,2));


//    eph.toc.time.year     = std::stoi( temp.substr(3,2));
//    eph.toc.time.month    = std::stoi( temp.substr(6,2));
//    eph.toc.time.day      = std::stoi( temp.substr(9,2));
//    eph.toc.time.hour     = std::stoi( temp.substr(12,2));
//    eph.toc.time.minute   = std::stoi( temp.substr(15,2));
//    eph.toc.time.second   = 0;
//    eph.toc.sec           = std::stod( temp.substr(17,5));

    eph.af0               = extractDouble(temp,22,19);
    eph.af1               = extractDouble(temp,41,19);
    eph.af2               = extractDouble(temp,60,19);

    // the 2th line
    temp = str.at(1);
    eph.iode               = extractDouble(temp,3,19);
    eph.Crs                = extractDouble(temp,22,19);
    eph.Deln               = extractDouble(temp,41,19);
    eph.M0                 = extractDouble(temp,60,19);

    // the 3th line
    temp = str.at(2);
    eph.Cuc               = extractDouble(temp,3,19);
    eph.e                 = extractDouble(temp,22,19);
    eph.Cus               = extractDouble(temp,41,19);
    eph.A                 = extractDouble(temp,60,19);

    // the 4th line
    temp = str.at(3);
    gtime.fromString(QString::fromStdString(temp.substr(3,19)),17);
    eph.toe = gtime.getSecond();

//    double tempDouble     = extractDouble(temp,3,19);
//    eph.toe.time          = floor(tempDouble);
//    eph.toe.sec           =  tempDouble - eph.toe.time;
    eph.Cic               = extractDouble(temp,22,19);
    eph.OMG0              = extractDouble(temp,41,19);
    eph.Cis               = extractDouble(temp,60,19);

    // the 5th line
    temp = str.at(4);
    eph.i0                = extractDouble(temp,3,19);
    eph.Crc               = extractDouble(temp,22,19);
    eph.omg               = extractDouble(temp,41,19);
    eph.OMGd              = extractDouble(temp,60,19);

    // the 6th line
    temp = str.at(5);
    eph.iDOT              = extractDouble(temp,3,19);
    eph.code              = extractDouble(temp,22,19);
    eph.toes              = extractDouble(temp,41,19);
    eph.flag              = extractDouble(temp,60,19);

    // the 7th line
    temp = str.at(6);
    eph.sva               = extractDouble(temp,3,19);
    eph.svh               = extractDouble(temp,22,19);
    eph.tgd               = extractDouble(temp,41,19);
    eph.iodc              = extractDouble(temp,60,19);

    // the 8th line
    temp = str.at(7);
//    eph.ttr               = extractDouble(temp,3,19);
    eph.fit               = extractDouble(temp,22,19);
    eph.reserved          = extractDouble(temp,41,19);
    eph.reserved01        = extractDouble(temp,60,19);
}

double Rinex3x::extractDouble(const string &str,int pos, int npos) const
{
    string temp = str.substr(pos,npos);
    temp.replace(15,1,"E");
    return std::stod(temp);
}

void Rinex3x::getEphData(vector<eph_t>& ephData) const
{
    ephData = Rinex3x::ephData;
}


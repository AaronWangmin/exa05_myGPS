#include <QCoreApplication>

#include <iostream>
#include <time.h>
using namespace  std;

#include "gpshead.h"
#include "rinex3x.h"
#include "gstring.h"
#include "gtime.h"
#include "satpos.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    cout <<"test: rinex3x" << endl;
    Rinex3x rinex;
    rinex.readRinex3("D:/exam_cs106/code_aaron_cs106/exa05_myGPS/brdc1730.16n");
    vector<eph_t> ephData;
    rinex.getEphData(ephData);
    cout.precision(20);
    cout << ephData.back().toe << endl;
    cout << ephData.back().toc << endl;
//    cout << ctime(&(ephData.back().toc)) << endl;

    cout <<"test: time" << endl;
    string test = "1980 1 6 00 00 00";
    gtime_t t;
    str2time(test,0,36,t);    
    cout <<"test.." <<  t.time <<endl;
    double gps1[]= {1980,1, 6,0,0,0};
    cout <<"gps1: " << epoch2time(gps1).time << endl;

    cout <<"test: GString, a subclass of QString." << endl;
    GString gstr( "123.345");
    cout << gstr.str2num(0,5) << endl;

    cout <<"test: GTime, a subclass of QDateTime." << endl;
    GTime gtime0;
    cout  << "constructor: GTime(), second =  " << gtime0.getSecond() << endl;
    GTime gtime1(234);
    cout  << "constructor: GTime(double d), second =  " << gtime1.getSecond() << endl;
    gtime0.fromString(gps0,17);
//    GTime gtime(gps0,17);
    cout.precision(20);
    cout  << "constructor: GTime(str,int), second =  "<< gtime0.getSecond() << endl;
    cout  << "getGtime(week,second), gps second =  "<< gtime0.gtime2second(1902,233472) << endl;

    cout <<"test: SatPos, a class" << endl;
    SatPos satPos;
    pointXYZ_t point3;
    satPos.getSatPos(point3);
    cout << "X: " << point3.X << ","
         << "Y: " << point3.Y << ","
         << "Z: " << point3.Z << endl;

    cout <<"test: pointXYZ_t, a struct" << endl;
    pointXYZ_t point;
    cout << "default constructor: point() " << "X: " << point.X << ","
                                            << "Y: " << point.Y << ","
                                            << "Z: " << point.Z << endl;
    pointXYZ_t point1(123,456,789);
    cout << "default constructor: point() " << "X: " << point1.X << ","
                                            << "Y: " << point1.Y << ","
                                            << "Z: " << point1.Z << endl;

    cout <<"test: eph_t, a struct" << endl;
    eph_t eph;
    cout << eph.A << "  " << eph.af0 << endl;



    return a.exec();
}

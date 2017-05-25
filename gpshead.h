#ifndef GPSHEAD
#define GPSHEAD

#include <QString>

#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

#include "gtime.h"

/* constants -----------------------------------------------------------------*/
const static double GM = 3.986004415E+14;      // 地球引力常数

const QString gps0 = "80 1 6 0 0 0";        // gps time reference, (1980 01 06 00 00 00)

const static double gpst0[]={1980,1, 6,0,0,0}; /* gps time reference */






/*  type definations--------------------------------------------------------  */

typedef struct{
    int year,month,day,hour,minute,second;  // 2017 05 14 13 57 30
}utc_t;

typedef struct{
    time_t time;    // time(s) expressed by standard time time_t
    double sec;     // fraction of second under 1 s
}gtime_t;

// ref: A6 Navigation message file -- GPS data record, rinex 3.0,P72.
//typedef struct{         // GPS broadcast ephemeris type
//    int sat;
//    gtime_t toc;
//    double af0,af1,af2;
//    double iode,Crs,Deln,M0;    // broadcast orbit-1
//    double Cuc,e,Cus,A;         // broadcast orbit-2
//    gtime_t toe;                // broadcast orbit-3
//    double Cic,OMG0,Cis;
//    double i0,Crc,omg,OMGd;     // broadcast orbit-4
//    double iDOT,code,toes,flag; // broadcast orbit-5
//    double sva,svh,tgd,iodc;    // broadcast orbit-6
//    gtime_t ttr;                 // broadcast orbit-7
//    double fit;
//    double reserved,reserved01;
//}eph_t;

typedef struct{

}rinex3Head_t;

struct eph_t{                   // GPS broadcast ephemeris type
    int sat;
    GTime toc;
    double af0,af1,af2;
    double iode,Crs,Deln,M0;    // broadcast orbit-1
    double Cuc,e,Cus,A;         // broadcast orbit-2
    GTime toe;                  // broadcast orbit-3
    double Cic,OMG0,Cis;
    double i0,Crc,omg,OMGd;     // broadcast orbit-4
    double iDOT,code,toes,flag; // broadcast orbit-5
    double sva,svh,tgd,iodc;    // broadcast orbit-6
    GTime ttr;                  // broadcast orbit-7
    double fit;
    double reserved,reserved01;

    eph_t();
};

struct pointXYZ_t{
    double X;
    double Y;
    double Z;

    pointXYZ_t();
    pointXYZ_t(double dx,double dy,double dz);

};

/*  time and string functions-----------------------------------------------  */
extern void strSplit(const string& str,
                     vector<string>& splited,const string& pattern);
//extern double str2num(const string& str,int pos,int npos);
extern int str2time(const string& str,int pos,int npos,gtime_t& t);
extern double timeDiff(gtime_t t1,gtime_t t2);
extern gtime_t epoch2time(const double *ep);
extern gtime_t gpst2time(int week, double sec);


#endif // GPSHEAD


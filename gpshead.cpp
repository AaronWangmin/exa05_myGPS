#include "gpshead.h"

pointXYZ_t::pointXYZ_t():X(0),Y(0),Z(0)
{

}

pointXYZ_t::pointXYZ_t(double dx, double dy, double dz):X(dx),Y(dy),Z(dz)
{

}

eph_t::eph_t():sat(0),toc(0),
       af0(0),af1(0),af2(0),
       iode(0),Crs(0),Deln(0),M0(0),
       Cuc(0),e(0),Cus(0),A(0),
       toe(0),
       Cic(0),OMG0(0),Cis(0),
       i0(0),Crc(0),omg(0),OMGd(0),
       iDOT(0),code(0),toes(0),flag(0),
       sva(0),svh(0),tgd(0),iodc(0),
       ttr(0),
       fit(0),
       reserved(0),reserved01(0)
{

}



/* split a string -------------------------------------------------------------
* split string to serveral substring by pattern
* args   : string &str        I   string ("aa bb cc")
*          string &splited    O   string ("aa" ,"bb","cc")
*-----------------------------------------------------------------------------*/
extern void strSplit(const string& s,
                     vector<string>& v,const string& c)
{
    string temp = s;
//    for(int i = 0;i < s.size();i++){
//       if( c == (s.at(s.find(c) +1))) s.erase(s.find(c),1);

//    }



    string::size_type pos1,pos2;
    pos1 = 0;
    pos2 = s.find(c);

    while(string::npos != pos2){
        v.push_back(s.substr(pos1,pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c,pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


/* string to number ------------------------------------------------------------
* convert substring in string to number
* args   : string &str        I   string ("... nnn.nnn ...")
*          int    pos,npos    I   substring position and width
* return : converted number (0.0:error)
*-----------------------------------------------------------------------------*/
//extern double str2num(const string& str,int pos,int npos)
//{
//    return stod( str.substr(pos,npos));
//}

/* string to time --------------------------------------------------------------
* convert substring in string to gtime_t struct
* args   : string &str        I   string ("... yyyy mm dd hh mm ss ...")
*          int    pos,npos    I   substring position and width
*          gtime_t *t         O   gtime_t struct
* return : status (0:ok,0>:error)
*-----------------------------------------------------------------------------*/
extern int str2time(const string& str,int pos,int npos,gtime_t& t)
{
    string temp = str.substr(pos,npos);
    vector<string> sub;
    strSplit(temp,sub," ");

    if(sub.size() != 6) return -1;
    double ep[6];
    for(int i = 0; i < 6; i++){
      ep[i] = stod(sub.at(i));
    }
    t = epoch2time(ep);

    return 0;
}

extern double timeDiff(gtime_t t1, gtime_t t2)
{
    return difftime(t1.time,t2.time) + t1.sec - t2.sec;
}

/* convert calendar day/time to time -------------------------------------------
* convert calendar day/time to gtime_t struct
* args   : double *ep       I   day/time {year,month,day,hour,min,sec}
* return : gtime_t struct
* notes  : proper in 1970-2037 or 1970-2099 (64bit time_t)
*-----------------------------------------------------------------------------*/
extern gtime_t epoch2time(const double *ep)
{
    const int doy[]={1,32,60,91,121,152,182,213,244,274,305,335};
    gtime_t time={0,0};
    int days,sec,year=(int)ep[0],mon=(int)ep[1],day=(int)ep[2];

    if (year<1970||2099<year||mon<1||12<mon) return time;

    /* leap year if year%4==0 in 1901-2099 */
    days=(year-1970)*365+(year-1969)/4+doy[mon-1]+day-2+(year%4==0&&mon>=3?1:0);
    sec=(int)floor(ep[5]);
    time.time=(time_t)days*86400+(int)ep[3]*3600+(int)ep[4]*60+sec;
    time.sec=ep[5]-sec;
    return time;
}

/* gps time to time ------------------------------------------------------------
* convert week and tow in gps time to gtime_t struct
* args   : int    week      I   week number in gps time
*          double sec       I   time of week in gps time (s)
* return : gtime_t struct
*-----------------------------------------------------------------------------*/
extern gtime_t gpst2time(int week, double sec)
{
    gtime_t t = epoch2time(gpst0);
    if (sec<-1E9||1E9<sec) sec=0.0;
    t.time += 86400*7*week + (int)sec;
    t.sec = sec - (int)sec;
    return t;
}


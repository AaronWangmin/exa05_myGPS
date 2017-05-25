#include "gpshead.h"
#include "satpos.h"

SatPos::SatPos():posSat({0,0,0})
{

}

void SatPos::eph2Pos(GTime &time, eph_t &eph)
{   
    // 计算卫星发射信息时刻与参考时刻的差 tk
    double tk = time.getSecond() - eph.toe.getSecond();

    // 计算卫星平近点角 Mk
    double A = pow((eph.A),2);                       //	卫星轨道长半轴
    double n0 = pow((GM /pow(A,3) ),0.5);		     // 计算平角速度
    double n = n0 + eph.Deln;			//  改正平角速度
    double Mk = eph.M0 + n * tk;			//  平近点角


}

void SatPos::getSatPos(pointXYZ_t &posSat) const
{
    posSat = SatPos::posSat;
}

//double SatPos::timeDiff(gtime_t t1, gtime_t t2)
//{
////    return ( t2.time.year - t1.time.year ) * 365 *24 *60 *60 +
////            t2.time.

//}

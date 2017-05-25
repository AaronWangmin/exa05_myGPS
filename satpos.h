#ifndef SATPOS_H
#define SATPOS_H

#include "rinex3x.h"


class SatPos
{
public:
    SatPos();
    void eph2Pos(gtime_t& time,eph_t& eph);
    void getSatPos(pointXYZ_t& posSat) const;
private:
    pointXYZ_t posSat;

};

#endif // SATPOS_H

#ifndef RINEX3X_H
#define RINEX3X_H

#include <QString>

#include <vector>
using namespace std;

#include "gpshead.h"

class Rinex3x
{
public:
    Rinex3x();
    void readRinex3(const QString& fileName);
    void getEphData(vector<eph_t>& ephData) const;

private:
    rinex3Head_t rinexhead3;
    vector<eph_t> ephData;

    // parse one record of ephemeris record, rinex2.x
    void parseEphRecord(eph_t& eph,const vector<string>& str) const;

    // extract a double from string included 'D' in rinex.
    double extractDouble(const string& str,int pos,int npos) const;

};

#endif // RINEX3X_H

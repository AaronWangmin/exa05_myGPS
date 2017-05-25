#ifndef GSTRING_H
#define GSTRING_H

#include <QString>
#include <vector>
using namespace std;


class GString : public QString
{
public:
    GString(const QString& str);

    /**
     * @brief str2num
     * @param pos       int       I   substring position
     * @param npos      int       I   substring width
     * @return converted number
     */
    double str2num(int pos,int npos) const;

private:
    QString gstring;
};

#endif // GSTRING_H

#ifndef ALOGFORMATTER_H
#define ALOGFORMATTER_H
#include "alogdata.h"
using namespace std;

class ALogFormatter
{
public:
    ALogFormatter();
    virtual string format(ALogData log);

};

#endif // ALOGFORMATTER_H

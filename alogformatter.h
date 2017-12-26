#ifndef ALOGFORMATTER_H
#define ALOGFORMATTER_H
#include "alogdata.h"
using namespace std;

class ALogFormatter
{
        friend class ALogger;
        friend class ALogBaseWriter;
public:
    ALogFormatter();
    virtual string format(ALogData log);
protected:
        ~ALogFormatter();

};

#endif // ALOGFORMATTER_H

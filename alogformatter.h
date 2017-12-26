#ifndef ALOGFORMATTER_H
#define ALOGFORMATTER_H
#include "alogdata.h"
using namespace std;
/*
 Default Formatter class.
 Each writer keeps a copy of this object to format its output if a derived formatter is not explicitly set.
 Its output is
[User] [Date] (Severity) message
[Arif Bilgin] [Tue Dec 26 02:07:18 2017] (Warning) :message 20

Subclass it to have different outputs such as json , sql query etc



*/



class ALogFormatter
{
        friend class ALogger;
        friend class ALogBaseWriter;
public:
    ALogFormatter();
    virtual string format(ALogData log);
protected:
        virtual ~ALogFormatter();

};

#endif // ALOGFORMATTER_H

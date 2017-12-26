#ifndef ALOGSTREAM_H
#define ALOGSTREAM_H


#include "alogbasewriter.h"
#include <fstream>
using namespace  std;
class ALogWriter : public ALogBaseWriter
{
public:
        ALogWriter();
protected:

    virtual void write(ALogData log);
    virtual ~ALogWriter();


};


#endif // ALOGSTREAM_H

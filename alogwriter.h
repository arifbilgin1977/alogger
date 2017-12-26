#ifndef ALOGSTREAM_H
#define ALOGSTREAM_H


#include "alogbasewriter.h"
#include <fstream>
using namespace  std;
/*
    stdout writer class.
    Useful for piped architectures


*/
class ALogWriter : public ALogBaseWriter
{
public:
        ALogWriter(ALogFormatter* formatter=NULL);
protected:

    virtual void write(ALogData log);
    virtual ~ALogWriter();


};


#endif // ALOGSTREAM_H

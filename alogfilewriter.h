#ifndef ALogStreamWriter_h
#define ALogStreamWriter_h
#include "alogbasewriter.h"
#include <fstream>
using namespace  std;
class ALogFileWriter : public ALogBaseWriter
{
    friend class ALogger;
public:
    ALogFileWriter(string fileName,ALogFormatter* formatter=NULL);
protected:
    virtual void write(ALogData log);
    virtual ~ALogFileWriter();
    fstream* m_fileStream;

};


#endif // ALOGBASEWRITER_H

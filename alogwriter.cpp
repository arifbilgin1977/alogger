#include "alogwriter.h"
#include "ostream"
#include <iostream>

ALogWriter::ALogWriter(ALogFormatter* formatter) : ALogBaseWriter(formatter)
{

}

ALogWriter::~ALogWriter()
{

}
void ALogWriter::write(ALogData log)
{
    printf ("%s\n",m_formatter->format(log).c_str());
}

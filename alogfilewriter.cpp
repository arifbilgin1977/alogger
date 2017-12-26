#include "alogfilewriter.h"
#include "alogbasewriter.h"
#include "alogger.h"
#include <iostream>


ALogFileWriter::ALogFileWriter(string fileName, ALogFormatter *formatter) : ALogBaseWriter(formatter)
{
    //ALogBaseWriter::ALogBaseWriter(formatter);
    m_fileStream=new fstream();
    m_fileStream->open (fileName, std::fstream::in | std::fstream::out | std::fstream::app);

}

ALogFileWriter::~ALogFileWriter()
{
    m_fileStream->flush();
    delete m_fileStream;
}
void ALogFileWriter::write(ALogData log)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    *m_fileStream << m_formatter->format(log) <<endl;

}

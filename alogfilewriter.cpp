#include "alogfilewriter.h"
#include "alogbasewriter.h"
#include "alogger.h"
#include <iostream>
class FileOpenException: public exception
{
  virtual const char* what() const throw()
  {
    return "Log File cannot be opened.";
  }
} myex;

ALogFileWriter::ALogFileWriter(string fileName, ALogFormatter *formatter) : ALogBaseWriter(formatter)
{
    //ALogBaseWriter::ALogBaseWriter(formatter);
    m_fileStream=new fstream();
    m_fileStream->open (fileName, std::fstream::in | std::fstream::out | std::fstream::app);
    if (!m_fileStream->is_open())
    {
        FileOpenException e;
        throw (&e);
    }

}

ALogFileWriter::~ALogFileWriter()
{
    m_fileStream->flush();
    delete m_fileStream;
}
void ALogFileWriter::write(ALogData log)
{
   // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    *m_fileStream << m_formatter->format(log) <<endl;

}

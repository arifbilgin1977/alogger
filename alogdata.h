#ifndef ALOGDATA_H
#define ALOGDATA_H
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
enum ALogSeverity {ALwarning , ALlow , ALmedium ,ALhigh, ALcritical};
/*
  class that encapsulates log data.
  Nothing special.
  sets the log time in constructor during creation.
*/


class ALogData
{
public:
    ALogData(string msg,ALogSeverity svrty,string user);
    string logMessage() const;
    ALogSeverity severity () const;
    string user() const;
    chrono::time_point<std::chrono::system_clock>  timeStamp() ;
    static string severityText(ALogSeverity);

private:
    string m_logMessage; //log message itself
    ALogSeverity m_severity; //
    string m_user; //just a custom string to give some information about caller (user)
    chrono::time_point<std::chrono::system_clock>  m_timeStamp; //timestamp of log , it is the time when log is reported not the time of writing to the media
};

#endif // ALOGDATA_H

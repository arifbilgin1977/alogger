#ifndef ALOGDATA_H
#define ALOGDATA_H
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
enum ALogSeverity {ALwarning , ALlow , ALmedium ,ALhigh, ALcritical};
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
    string m_logMessage;
    ALogSeverity m_severity;
    string m_user; //never use this pointer except value of it as a memory address.
    chrono::time_point<std::chrono::system_clock>  m_timeStamp;
};

#endif // ALOGDATA_H

#include "alogdata.h"

ALogData::ALogData(string msg, ALogSeverity svrty, string user) :
    m_logMessage(msg),
    m_severity(svrty),
    m_user(user)
{
    //get current time stamp
    chrono::time_point<std::chrono::system_clock> e;
    m_timeStamp=std::chrono::system_clock::now();


}

string ALogData::logMessage() const
{
    return m_logMessage;
}

ALogSeverity ALogData::severity() const
{
    return m_severity;
}

string ALogData::user() const
{
    return m_user;
}

chrono::time_point<std::chrono::system_clock>  ALogData::timeStamp()
{
    return m_timeStamp;
}
//enum Severity {warning , low , medium ,high, critical};
string ALogData::severityText(ALogSeverity s)
{
    switch (s)
    {
    case 0:
        return "Warning";
    case 1:
        return "Low";
    case 2:
        return "medium";
    case 3:
        return "high";
    case 4:
        return "critical";
    default:
        return "undefined";

    }


}


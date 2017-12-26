#include "alogformatter.h"
#include "chrono"

ALogFormatter::ALogFormatter()
{

}
//This is not a very efficient formatting routine ,needs to be worked on FIX ME
string ALogFormatter::format(ALogData log)
{
    string rv;
    time_t timeStamp = std::chrono::system_clock::to_time_t(log.timeStamp());
    rv=rv+"["+log.user()+"] [" + std::ctime(&timeStamp) + "] ("+ALogData::severityText(log.severity())+")"+" :"+log.logMessage();
    rv.erase(std::remove(rv.begin(), rv.end(), '\n'), rv.end());
    return rv;

}

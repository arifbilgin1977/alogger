#ifndef ALOGGER_H
#define ALOGGER_H
#include <stdio.h>
#include <ostream>
#include <list>
#include <queue>
#include <thread>
#include "alogbasewriter.h"
#include "alogdata.h"
/*
    Primary Logging class that encapsulates other aspects of the ALogger library.
    It maintains its own thread to manage writer(subscribers) threads.
    Error handling relies on exceptions but needs enhancements.
    overloads << and () operators for data pushing.

    supports 3 different logging mechanism:
    logger << string;
    logger(severity) << string;
    logger (severity,user) << string
*/


class ALogger
{
public:
    ALogger(ALogBaseWriter *writer=NULL);
    ~ALogger();
    ALogger& operator << (const std::string logData);
    ALogger& operator () (const ALogSeverity svr);
    ALogger& operator () (const ALogSeverity svr,string user);
    void registerNewWriter(ALogBaseWriter* newWriter);

private:

    void WorkerFunction();
    void finalizeThreads();
    bool dying();
    void die();


    std::queue<ALogData> m_logs;
    std::mutex m_queueGuard;
    std::mutex m_writerListGuard;
    std::mutex m_DyingGuard;
    std::thread* m_workerThread;
    std::list<ALogBaseWriter*> m_streams;
    bool m_dying;
    ALogSeverity m_severity; //state variable for most recent severity assigned by ()
    string m_user; //state variable for most recent user name assigned by () operator


};
#endif // ALOGGER_H

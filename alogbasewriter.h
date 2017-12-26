#ifndef ALogBaseWriter_h
#define ALogBaseWriter_h
#include <ostream>
#include <thread>
#include "alogdata.h"
#include "queue"
#include "alogformatter.h"

class ALogger;

using namespace  std;

class ALogBaseWriter
{
    friend class ALogger;
public:
    ALogBaseWriter(ALogFormatter *formatter=NULL);
    void die();
    bool dying();
    bool pushLog(ALogData log);
    bool join();
    std::condition_variable* condVariable(){return &m_condition;}
    mutex* acquireLock(){return &m_logQueueGuard;}
protected:
    void workerFunction();
    virtual void write(ALogData log)=0;
    virtual ~ALogBaseWriter();
    mutex m_dyingGuard;
    mutex m_logQueueGuard;
    queue<ALogData> m_logQueue; // logs waiting to be consumed
    bool m_dying;
    std::thread* m_workerThread;
    ALogFormatter* m_formatter;
    std::condition_variable m_condition;

};

#endif // ALogBaseWriter

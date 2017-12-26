#include "alogbasewriter.h"
#include "alogger.h"
#include <iostream>

ALogBaseWriter::ALogBaseWriter(ALogFormatter* formatter) : m_formatter(formatter)
{

    if(!m_formatter)
        m_formatter=new ALogFormatter();

    //create the internal thread and begin consuming data
    m_workerThread=new std::thread(&ALogBaseWriter::workerFunction,this);


}

ALogBaseWriter::~ALogBaseWriter()
{
    //make sure worker thread is joined and terminated gracefully
    if(m_workerThread->joinable())
        m_workerThread->join();
    //clean up heap objects
    delete m_workerThread;
    delete m_formatter;

}

void ALogBaseWriter::die() //die flag is set to ture, whenever thread has no jobs and dying is set , it breaks the loop
{
    m_dyingGuard.lock();
    m_dying = true;
    m_dyingGuard.unlock();
}

bool ALogBaseWriter::dying() //check if thread is supposed to be terminated
{
    m_dyingGuard.lock();
    bool rv= m_dying;
    m_dyingGuard.unlock();
    return rv;
}

bool ALogBaseWriter::pushLog(ALogData log)
{
    //FIX ME , put a maximum limit to prevent log spamming , how many logs in queue tolarated ?
    m_logQueue.push(log);
    return true; //when we have a maz limit this function may return false depending on queue size FIX ME

}

bool ALogBaseWriter::join()
{
    if(!m_workerThread->joinable())
        return false;
    m_workerThread->join();
    return true;

}

void ALogBaseWriter::workerFunction()
{
    while(1)
    {
        //    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<mutex> locker(m_logQueueGuard);
        if(!dying())
            m_condition.wait(locker);
        if(m_logQueue.size()==0)
        {
            locker.unlock();
            if (dying())
                return;
            continue;
        }

        /*get a copy of data to be consumed and release the lock before consuming.*/

        ALogData lData=m_logQueue.front();
        m_logQueue.pop();
        locker.unlock();
        write(lData);
    }

}


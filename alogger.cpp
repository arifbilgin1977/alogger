#include "alogger.h"
#include <iostream>
#include "alogwriter.h"

std::condition_variable level1Condition;


ALogger::ALogger(ALogBaseWriter *writer) : m_severity(ALwarning)
{
    if(!writer)
        writer = new ALogWriter();
    this->registerNewWriter(writer); //default stream , writing to std out
    m_workerThread=new std::thread(&ALogger::WorkerFunction,this);

}

ALogger::~ALogger()
{
    die();
    finalizeThreads();


}
ALogger& ALogger::operator << (const std::string logData)
{

    std::unique_lock<mutex> locker(m_queueGuard);
    m_logs.push(ALogData(logData,m_severity,m_user));
    locker.unlock();
    level1Condition.notify_all();
    return *this;
}
ALogger& ALogger::operator () (const ALogSeverity svr)
{
    m_severity=svr;
    return *this;
}
ALogger& ALogger::operator ()(const ALogSeverity svr,string user)
{
    m_severity=svr;
    m_user=user;
    return *this;


}

/*Thread safe stream registration routine
 * Remember user provided streams should never be used again by the user
 * once a stream is registered with ALogger framework it is owned by a thread and deleted by the same thread.
 * We may need a object factory for custom ostreams.!!!!!!!!!
 *
*/

void ALogger::registerNewWriter(ALogBaseWriter *newWriter)
{
    m_writerListGuard.lock();
    m_streams.push_back(newWriter);
    m_writerListGuard.unlock();
}

void ALogger::finalizeThreads()
{
    /*
     Join all threads in writer classes here , we do not want writer objects destructor to do this to avoid ugly deadlocks
     This way even if writer class is deleted , its destructor will wait until writer worker threads finish their jobs
     */

    //lets wait for our own thread to finish its job first
    if(m_workerThread->joinable())
        m_workerThread->join();
    list<ALogBaseWriter*>::iterator it= m_streams.begin();
    while (it != m_streams.end())
    {

        if((*it)->join())    // what if writer thread can not join?? FIX ME
            delete (*it);
        it++;
    }
    delete m_workerThread;


}

bool ALogger::dying()
{
    m_DyingGuard.lock();
    bool rv=m_dying;
    m_DyingGuard.unlock();
    return rv;
}

void ALogger::die()
{
    std::unique_lock<mutex> locker(m_queueGuard);
    m_dying = true;
    locker.unlock();
    level1Condition.notify_all();




}




/*
 * this function is run within ALogger object thread
 * it watches the log queue and distribute the log objects to its stream containers.
 * All registered containers get the log data and process it in their own worker thread
*/

void ALogger::WorkerFunction()
{
    while(1)
    {
        //     m_queueGuard.lock();
        std::unique_lock<mutex> locker(m_queueGuard);
        if(!dying())
            level1Condition.wait(locker);
        if(m_logs.empty())
        {
            //check if dying
            if(dying())
            {
                locker.unlock();
                //send die signal to all subscribers
                list<ALogBaseWriter*>::iterator it= m_streams.begin();
                while (it != m_streams.end())
                {

                    std::unique_lock<mutex> locker(*(*it)->acquireLock());
                    (*it)->die();
                    locker.unlock();
                    (*it)->condVariable()->notify_all();
                    it++;
                }
                //now end the loop
                return;
            }
        }
        else
        {
            ALogData lData=m_logs.front();
            m_logs.pop();
            locker.unlock();
            list<ALogBaseWriter*>::iterator it=m_streams.begin();
            while (it != m_streams.end())
            {
                std::unique_lock<mutex> locker(*(*it)->acquireLock());
                (*it)->pushLog(lData);
                locker.unlock();
                (*it)->condVariable()->notify_all();
                it++;
            }

        }
        continue;
    }


}

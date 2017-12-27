# alogger
Asynchronous , non-blocking C++11 Logger Library free of known multi-threading issues such as busy spins or starving threads.
It is fast , reliable and very easy to use. No third party dependencies. ALogger supports multiple instances of logger and multiple writers for each logger instance.

## Class Definitions
### ALogBaseWriter ALogFileWriter ALogWriter<br />
Writer class is a thread wrapper that does the real I/O operations. It is derived from abstract ALogBaseWriter class and implements its own write function.Currently there are two writer classes , file writer (ALogFileWriter) and stdout writer (AlogWriter). To define a new writer , all you need to do is subclass ALogBaseWriter and implement your write function.For instance one can implement it in a way to post data to a REST API or a Database. Flexible nature of the library makes it very easy to extend.

### Alogger<br />
Log manager : Log manager is the container class of writers.It serves as a centralized log entry point and maintains multiple writers.Logs pushed to the log manager is consumed by each writer registered to it.

### ALogFormatter<br />
Formatters  : A Formatter formats the logger data before writing it. If a formatter is not explicitly assigned to a writer, default formatter is used.By subclassing your ALogFormatter and overrriding format function you can define your own output.

### Enum ALogSeverity<br />
Enum for severity levels for logs.Warning , Low,medium, High and critical.

### User<br />
A Custom string that gives information about the user.

## Installation
Add header and source files to your C++11 project.

## Usage
```c++
#include <iostream>
#include "alogger.h"
#include <fstream>
#include "alogfilewriter.h"
#include "alogwriter.h"

using namespace std;

class MyFormatter : public ALogFormatter
{
public:
    virtual string format(ALogData log)
    {

        return "custom output with only log message:" + log.logMessage();

    }


};

void thread1_func(ALogger* logger)
{
    for (auto id=0 ; id <50;id++)
        *logger << "thread 1 logging " + std::to_string(id);

}

void thread2_func(ALogger* logger)
{
    for (auto id=0 ; id <50;id++)
        *logger << "thread 2 logging " + std::to_string(id);

}


int main(int , char**)
{
    //Create a Logger object.If a ALogBaseWriter object is not provided , it creates a ALogWriter and register it as the first writer object.
    ALogger myLogger; //Logger with default std out writer

    //add a second writer that writes to file test1.txt
    myLogger.registerNewWriter(new ALogFileWriter("test1.txt"));

    //one more stdout writers
    myLogger.registerNewWriter(new ALogWriter());


    //create two threads to test threaded publishers
    thread t1=thread(&thread1_func,&myLogger);
    thread t2=thread(&thread2_func,&myLogger);

    //at this point logs are written to 3 different target , 2 on stdout one copy in test1.txt
    myLogger << "My first Log"; // now you should see My first log twice in console and also in 1 entry in test1.txt. with default severity and no User
    myLogger (ALcritical) << "This is a very critical log"; //severity is changed
    myLogger (ALlow,"main.cpp (line :32)") << "something is not right here"; //user info is added to the log

    //add another writer with custom Formatter
    myLogger.registerNewWriter(new ALogFileWriter("customLog.txt",new MyFormatter()));

    //new writer writes logs with a custom format defined in class MyFormatter

    myLogger << " This log is channeled to 4 diffferent writer";
    t1.join();
    t2.join();


    return 0;
}

```

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
## Demo command line tool - alogbroadcaster <br />
ALogBroadcaster is a small utility that takes log texts from stdin and writes to multiple files.<br />
It has a small set of commands to change two states of logger , severity and user.<br />
Documentation of this tool is:<br />
Log Broadcaster (v:0.99)<br />
Utility to write stdin logs to multiple files.<br />
Usage:<br />
ALogger [file list]<br />
Example :<br />
alogger file1.txt file2.txt file3.txt<br />
<br />
Commands:<br />
:quit<br />
 terminates the program<br />
:warning<br />
 Switches log severity to warning<br />
:low<br />
 Switches log severity to low<br />
:medium<br />
 Switches log severity to medium<br />
:high<br />
 Switches log severity to high<br />
:critical<br />
 Switches log severity to critical<br />
:user:user_name<br />
 Switches user to user_name<br />

 Example:
```bash
$ ./alogger file1.txt file2.txt
Starting Logging
log text 1
log text 2
:critical
these logs should be marked as critical
:warning
now only warnings
:user:Arif Bilgin
these logs are coming from Arif
test
gg
sdfasdfasdfsdfdsf
.quit
bye!
$ cat file1.txt
[ALogger Demo] [Tue Dec 26 21:05:30 2017] (Warning) :Starting Logging
[ALogger Demo] [Tue Dec 26 21:05:38 2017] (Warning) :log text 1
[ALogger Demo] [Tue Dec 26 21:05:43 2017] (Warning) :log text 2
[ALogger Demo] [Tue Dec 26 21:05:57 2017] (critical) :these logs should be marked as critical
[ALogger Demo] [Tue Dec 26 21:06:06 2017] (Warning) :now only warnings
[Arif Bilgin] [Tue Dec 26 21:06:21 2017] (Warning) :these logs are coming from Arif
[Arif Bilgin] [Tue Dec 26 21:06:25 2017] (Warning) :test
[Arif Bilgin] [Tue Dec 26 21:06:26 2017] (Warning) :gg
[Arif Bilgin] [Tue Dec 26 21:06:27 2017] (Warning) :sdfasdfasdfsdfdsf
$ cat file2.txt
[ALogger Demo] [Tue Dec 26 21:05:30 2017] (Warning) :Starting Logging
[ALogger Demo] [Tue Dec 26 21:05:38 2017] (Warning) :log text 1
[ALogger Demo] [Tue Dec 26 21:05:43 2017] (Warning) :log text 2
[ALogger Demo] [Tue Dec 26 21:05:57 2017] (critical) :these logs should be marked as critical
[ALogger Demo] [Tue Dec 26 21:06:06 2017] (Warning) :now only warnings
[Arif Bilgin] [Tue Dec 26 21:06:21 2017] (Warning) :these logs are coming from Arif
[Arif Bilgin] [Tue Dec 26 21:06:25 2017] (Warning) :test
[Arif Bilgin] [Tue Dec 26 21:06:26 2017] (Warning) :gg
[Arif Bilgin] [Tue Dec 26 21:06:27 2017] (Warning) :sdfasdfasdfsdfdsf
$
```

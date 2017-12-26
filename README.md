# alogger
Asynchronous , non-locking C++ Logger Library free of know multi-threading issues such  issues busy spins or starving threads.
It is fast , realiable and very easy to use. No third party dependencies.
# Class Definitions
Writers (ALogFileWriter ALogWriter): Writer class is a thread wrapper that does the real I/O operations. It is derived from abstract ALogBaseWriter class and implements its own write function.Currently there are two writer classes , file writer (ALogFileWriter) and stdout writer (AlogWriter). To define a new writer , all you need to do is subclass ALogBaseWriter and implement your write function.For instance one can implement it in a way to post data to a REST API or a Database. Flexible nature of the library makes it very easy to extend.

Log manager (Alogger): Log manager is the container class of writers.It serves as a centralized log entry point and maintains multiple writers.Logs pushed to the log manager is consumed by each writer registered to it.

Formatters (ALogFormatter) : A Formatter formats the logger data before writing it. If a formatter is not explicitly assigned to a writer, default formatter is used.By subclassing your ALogFormatter and overrriding format function you can define your own output.

Log Severity (Enum ALogSeverity): Severity levels for logs.Warning , Low,medium, High and critical.

User : A Custom string that gives information about the user.

## Installation
Add header and source files to your C++11 project or include alogger_all.hpp to any C++ module.

## Usage
```c++
//define a custom output for writers
class MyFormatter : public ALogFormatter
{
public:
    virtual string format(ALogData log)
    {

        return "custom output with only log message:" + log.logMessage();

    }


};
int main(int , char**)
{
    //Create a Logger object.If a ALogBaseWriter object is not provided , it creates a ALogWriter and register it as the first writer object.
    ALogger myLogger; //Logger with default std out writer

    //adds a second writer that writes to file test1.txt
    myLogger.registerNewWriter(new ALogFileWriter("test1.txt"));

    //one more stdout writers
    myLogger.registerNewWriter(new ALogWriter());


    //at this point logs are written to 3 different target , 2 on stdout one copy in test1.txt
    myLogger << "My first Log"; // now you should see My first log twice in console and also in 1 entry in test1.txt. with default severity and no User
    myLogger (ALcritical) << "This is a very critical log"; //severity is changed
    myLogger (ALlow,"main.cpp (line :32)") << "something is not right here"; //user info is added to the log

    //add another writer with custom Formatter
    myLogger.registerNewWriter(new ALogFileWriter("customLog.txt",new MyFormatter()));

    //new writer writes logs with a custom format defined in class MyFormatter

    myLogger << " This log is channeled to 4 diffferent writer";


    return 0;
}





```

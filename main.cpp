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



int main(int , char**)
{
    //Default constructor. Creates a Logger object.If a ALogBaseWriter object is not provided , it creates a ALogWriter and register it as the first writer object.
    ALogger myLogger; //Logger with default std out writer

    ALogFormatter f;

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

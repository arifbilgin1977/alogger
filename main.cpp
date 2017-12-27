/*
Log Broadcaster (v:0.99)
Utility to write stdin logs to multiple files.
Usage:
ALogger [file list]
Example :
alogger file1.txt file2.txt file3.txt

Commands:
:quit
 terminates the program
:warning
 Switches log severity to warning
:low
 Switches log severity to low
:medium
 Switches log severity to medium
:high
 Switches log severity to high
:critical
 Switches log severity to critical
:user:user_name
 Switches user to user_name

*/



#include <iostream>
#include "alogger.h"
#include <fstream>
#include "alogfilewriter.h"
#include "alogwriter.h"
using namespace std;

ALogSeverity severity=ALwarning;
string user="ALogger Demo";
bool processCommand(string line)
{
    if (line==":quit")
        return false;
    if(line==":warning")
        severity=ALwarning;
    if(line==":low")
        severity=ALlow;
    if(line==":medium")
        severity=ALmedium;
    if(line==":high")
        severity=ALhigh;
    if(line==":critical")
        severity=ALcritical;
    if(line.substr(0,6)==":user:")
        user=line.substr(6);
    return true;
}

static void printHelp()
{
    printf ("Log Broadcaster (v:0.99)\n");
    printf ("Utility to write stdin logs to multiple files.\n");
    printf ("Usage:\n");
    printf ("ALogger [file list]\n");
    printf ("Example usage:\n");
    printf ("alogger file1.txt file2.txt file3.txt\n\n");
    printf ("Commands:\n");
    printf (":quit\n terminates the program\n");
    printf (":warning\n Switches log severity to warning\n");
    printf (":low\n Switches log severity to low\n");
    printf (":medium\n Switches log severity to medium\n");
    printf (":high\n Switches log severity to high\n");
    printf (":critical\n Switches log severity to critical\n");
    printf (":user:user_name\n Switches user to user_name\n");
}

int main(int cnt , char** args)
{
    std::list<std::string> files;

    for (int id=1;id < cnt ;id++)
    {
        if((string(args[id])=="--help" || string(args[id])=="-help") || string(args[id])=="/help")
            printHelp();
        else //file name
            files.push_back(args[id]);
    }
    ALogger* logger;
    if(files.empty())
        logger=new ALogger(); //write stdout
    else
    {
        list<string>::iterator it=files.begin();
        logger=new ALogger(new ALogFileWriter(*it));
        it++;
        while (it != files.end())
        {
            logger->registerNewWriter(new ALogFileWriter(*it));
            it++;
        }

    }
    for (string line; getline(std::cin, line);) {
        //   cout << line;
        if(line[0]==':')
        {
            if(!processCommand(line))
                break;
        }
        else
        {
            (*logger)(severity,user) << line ;
        }
    }
    delete logger;
    return 0;

}

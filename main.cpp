#include <iostream>
#include "alogger.h"
#include <fstream>
#include "alogfilewriter.h"
#include "alogwriter.h"

using namespace std;

int main(int , char**)
{
    ALogger log(new ALogWriter());
    log.registerNewWriter(new ALogWriter());
    log.registerNewWriter(new ALogWriter());
    log.registerNewWriter(new ALogFileWriter("deneme.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme2.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme3.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme2.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme4.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme5.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme6.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme7.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme8.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme9.txt"));
    log.registerNewWriter(new ALogFileWriter("deneme10.txt"));
    for (int id=0 ; id < 100 ; id++)
    {
      //  std::this_thread::sleep_for(std::chrono::milliseconds(150));
        log(ALwarning,"Arif Bilgin") << "message " + std::to_string(id);

    }


    return 0;
}

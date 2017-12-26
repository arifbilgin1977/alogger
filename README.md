# alogger
Asynchronous C++ Logger Library.
# Legend
Writers : Writer class is a thread wrapper that does the real I/O operations. It is derived from abstract ALogBaseWriter class and implements its own write function.Currently there are two writer classes , file writer (ALogFileWriter) and stdout writer (AlogWriter). To define a new writer , all you need to do is subclass ALogBaseWriter and implement your write function.For instance one can implement it in a way to post data to a REST API or a Database. Flexible nature of the library makes it very easy to extend.

Log manager: Log manager is the container class of writers.It serves as a centralized log entry point and maintains multiple writers.Logs pushed to the log manager is consumed by each writer registered to it.

Formatters : A Formatter formats the logger data before writing it. If a formatter is not explicitly assigned to a writer, default formatter is used.By subclassing your ALogFormatter and overrriding format function you can define your own output.

Log Severity : Severity levels for logs.Warning , Low,medium, High and critical.

User : A Custom string that gives information about the user.

## Installation
Add header and source files to your C++11 project or include alogger_all.hpp to any C++ module.

## API

Class: Alogger

//Default constructor. Creates a Logger object.If a ALogBaseWriter object is not provided , it creates a ALogWriter and register it as the first writer object.

Alogger myLogger(); //creates one stdout writers

//adds a second writer that writes to file test1.txt
myLogger.registerNewWriter(new ALogFileWriter("test1.txt"));

mylLogger.registerNewWriter(new ALogWriter()); //one more stdout writers
//at this point logs are written to 3 different target , 2 on stdout one copy in test1.txt


mylLogger << "My first Log"; // now you should see My first log twice in console and also in 1 entry in test1.txt. with default severity and no User
mylLogger (ALcritical) << "This is a very critical log"; //severity is changed
mylLogger (ALLow,"main.cpp") << "something is not right here"; //user info is added to this console

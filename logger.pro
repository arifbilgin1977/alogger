TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    alogger.cpp \
    alogdata.cpp \
    alogbasewriter.cpp \
    alogfilewriter.cpp \
    alogwriter.cpp \
    alogformatter.cpp

HEADERS += \
    alogger.h \
    alogdata.h \
    alogbasewriter.h \
    alogfilewriter.h \
    alogwriter.h \
    alogformatter.h

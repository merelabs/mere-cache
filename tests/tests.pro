QT += testlib
QT -= gui

CONFIG += qt console
CONFIG -= app_bundle
CONFIG += no_testcase_installs
CONFIG += object_parallel_to_source

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/testfifocache.cpp \
    src/testlfucache.cpp \
    src/testlifocache.cpp \
    src/testlrucache.cpp \
    src/testtlrucache.cpp

HEADERS += \
    src/testfifocache.h \
    src/testlfucache.h \
    src/testlifocache.h \
    src/testlrucache.h \
    src/testtlrucache.h

#include(../mere-xdg-src.pri)

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib
LIBS += -lmere-cache

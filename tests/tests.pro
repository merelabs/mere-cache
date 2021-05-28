QT += testlib
QT -= gui

CONFIG += qt console
CONFIG -= app_bundle
CONFIG += no_testcase_installs
CONFIG += object_parallel_to_source

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/testarccache.cpp \
    src/testfifocache.cpp \
    src/testlfucache.cpp \
    src/testlifocache.cpp \
    src/testlrucache.cpp \
    src/testmfucache.cpp \
    src/testmrucache.cpp \
    src/testtlrucache.cpp

HEADERS += \
    src/testarccache.h \
    src/testfifocache.h \
    src/testlfucache.h \
    src/testlifocache.h \
    src/testlrucache.h \
    src/testmfucache.h \
    src/testmrucache.h \
    src/testtlrucache.h

#include(../mere-xdg-src.pri)

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib
LIBS += -lmere-cache

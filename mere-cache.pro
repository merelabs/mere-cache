#QT      = core
CONFIG += c++11
CONFIG += shared

TARGET = mere-cache
VERSION= 0.0.1b
TEMPLATE = lib

DEFINES += LIB_CODE=\\\"cache\\\"
DEFINES += LIB_NAME=\\\"$$TARGET\\\"
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"
DEFINES += MERE_XDG_LIB

SOURCES += \
    src/cache.cpp \
    src/arccache.cpp \
    src/fifocache.cpp \
    src/lfucache.cpp \
    src/lifocache.cpp \
    src/lrfucache.cpp \
    src/lrucache.cpp \
    src/mfucache.cpp \
    src/mrucache.cpp \
    src/tlrucache.cpp

HEADERS += \
    src/cache.h \
    src/arccache.h \
    src/fifocache.h \
    src/global.h \
    src/lfucache.h \
    src/lifocache.h \
    src/lrfucache.h \
    src/lrucache.h \
    src/mfucache.h \
    src/mrucache.h \
    src/tlrucache.h


INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib

#
# Install
#
unix {
    target.path = /usr/local/lib
    INSTALLS += target

    INSTALL_PREFIX = /usr/local/include/mere/cache
    for(header, HEADERS) {
        sdir = $${dirname(header)}
        equals(sdir, "src") {
            sdir = ""
        } else {
            sdir = $$replace(sdir, "src/", "")
        }
#        message($$sdir)

        path = $${INSTALL_PREFIX}$${sdir}
#        message($$path)
        eval(headers_$${path}.files += $$header)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }
}


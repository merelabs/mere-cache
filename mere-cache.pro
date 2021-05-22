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
    src/linkcache.cpp \
    src/policy/arccache.cpp \
    src/cache.cpp \
    src/diskcache.cpp \
    src/policy/fifocache.cpp \
    src/policy/lfucache.cpp \
    src/policy/lifocache.cpp \
    src/policy/lrfucache.cpp \
    src/policy/lrucache.cpp \
    src/policy/mfucache.cpp \
    src/policy/mrucache.cpp \
    src/softlinkcache.cpp \
    src/policy/tlrucache.cpp

HEADERS += \
    src/linkcache.h \
    src/policy/arccache.h \
    src/cache.h \
    src/diskcache.h \
    src/policy/fifocache.h \
    src/global.h \
    src/policy/lfucache.h \
    src/policy/lifocache.h \
    src/policy/lrfucache.h \
    src/policy/lrucache.h \
    src/policy/mfucache.h \
    src/policy/mrucache.h \
    src/softlinkcache.h \
    src/policy/tlrucache.h

#DISTFILES +=

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lmere-utils

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


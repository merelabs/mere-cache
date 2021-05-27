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
#    src/arccache.cpp \
#    src/lifocache.cpp \
    src/lfucache.cpp \
#    src/lirscache.cpp \
#    src/lrfucache.cpp \
#    src/lrucache.cpp \
#    src/mfucache.cpp \
#    src/mrucache.cpp \
#    src/tlrucache.cpp

HEADERS += \
    src/cache.hpp \
    src/fifocache.hpp \
    src/lfucache.hpp \
    src/lifocache.hpp \
    src/lrucache.hpp \
#    src/tlrucache.hpp \
#    src/lirscache.h \
#    src/lrfucache.h \
#    src/mfucache.h \
#    src/mrucache.h \
    src/global.h


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
        path = $${INSTALL_PREFIX}$${sdir}
        eval(headers_$${path}.files += $$header)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }
}


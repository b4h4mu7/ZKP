#-------------------------------------------------
#
# Project created by QtCreator 2013-11-18T17:24:24
#
#-------------------------------------------------

QT       -= gui

TARGET = ZKPDummy
TEMPLATE = lib

DEFINES += ZKPDUMMY_LIBRARY
QMAKE_CXXFLAGS += -Wall -Werror -std=c++11

SOURCES += \
    ResponseDummy.cpp \
    ProofDummy.cpp \
    ProverDummy.cpp \
    VerifierDummy.cpp \
    PrivateKeyDummy.cpp \
    PublicKeyDummy.cpp

HEADERS += \
    ResponseDummy.h \
    ProofDummy.h \
    ProverDummy.h \
    VerifierDummy.h \
    PrivateKeyDummy.h \
    PublicKeyDummy.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZKP/release/ -lZKP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZKP/debug/ -lZKP
else:unix: LIBS += -L$$OUT_PWD/../ZKP/ -lZKP

INCLUDEPATH += $$PWD/../ZKP
DEPENDPATH += $$PWD/../ZKP

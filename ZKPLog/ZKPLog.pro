#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T10:28:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = ZKPLog
TEMPLATE = lib

DEFINES += ZKPLOG_LIBRARY
QMAKE_CXXFLAGS += -Wall -Werror -std=c++11

SOURCES += \
    ProofLog.cpp \
    PrivateKeyLog.cpp \
    ProverLog.cpp \
    PublicKeyLog.cpp \
    ResponseLog.cpp \
    VerifierLog.cpp

HEADERS += \
    ProofLog.h \
    PrivateKeyLog.h \
    ProverLog.h \
    PublicKeyLog.h \
    ResponseLog.h \
    VerifierLog.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZKP/release/ -lZKP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZKP/debug/ -lZKP
else:unix: LIBS += -L$$OUT_PWD/../ZKP/ -lZKP

INCLUDEPATH += $$PWD/../ZKP
DEPENDPATH += $$PWD/../ZKP

unix|win32: LIBS += -lcrypto++

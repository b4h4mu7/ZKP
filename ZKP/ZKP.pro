#-------------------------------------------------
#
# Project created by QtCreator 2013-11-15T16:27:16
#
#-------------------------------------------------

QT       -= core gui

TARGET = ZKP
TEMPLATE = lib

DEFINES += ZKP_LIBRARY
QMAKE_CXXFLAGS += -Wall -Werror -std=c++11

SOURCES += \
    Prover.cpp \
    Verifier.cpp \
    IterativeVerifier.cpp \
    IterativeProver.cpp \
    PrivateKey.cpp

HEADERS += \
    Prover.h \
    Verifier.h \
    Challenge.h \
    Proof.h \
    Response.h \
    IterativeVerifier.h \
    IterativeProver.h \
    Cloneable.h \
    PrivateKey.h \
    PublicKey.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix|win32: LIBS += -lcrypto++

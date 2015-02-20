#-------------------------------------------------
#
# Project created by QtCreator 2013-11-19T11:44:45
#
#-------------------------------------------------

QT       -= gui

TARGET = QtZKP
TEMPLATE = lib

DEFINES += QTZKP_LIBRARY
QMAKE_CXXFLAGS += -Wall -Werror -std=c++11

SOURCES += \
    QtIterativeProver.cpp \
    QtIterativeVerifier.cpp

HEADERS += \
    QtIterativeProver.h \
    QtIterativeVerifier.h

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

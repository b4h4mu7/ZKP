#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T17:10:44
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_ZKPLogUnitTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS += -Wall -Werror -std=c++11

SOURCES += tst_ZKPLogUnitTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZKP/release/ -lZKP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZKP/debug/ -lZKP
else:unix: LIBS += -L$$OUT_PWD/../ZKP/ -lZKP

INCLUDEPATH += $$PWD/../ZKP
DEPENDPATH += $$PWD/../ZKP

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZKPLog/release/ -lZKPLog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZKPLog/debug/ -lZKPLog
else:unix: LIBS += -L$$OUT_PWD/../ZKPLog/ -lZKPLog

INCLUDEPATH += $$PWD/../ZKPLog
DEPENDPATH += $$PWD/../ZKPLog

unix|win32: LIBS += -lcrypto++

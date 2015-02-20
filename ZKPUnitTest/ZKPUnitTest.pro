#-------------------------------------------------
#
# Project created by QtCreator 2013-11-18T17:19:39
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_ZKPUnitTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS += -Wall -Werror -std=c++11

SOURCES += \
    tst_ZKPUnitTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZKP/release/ -lZKP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZKP/debug/ -lZKP
else:unix: LIBS += -L$$OUT_PWD/../ZKP/ -lZKP

INCLUDEPATH += $$PWD/../ZKP
DEPENDPATH += $$PWD/../ZKP

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtZKP/release/ -lQtZKP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtZKP/debug/ -lQtZKP
else:unix: LIBS += -L$$OUT_PWD/../QtZKP/ -lQtZKP

INCLUDEPATH += $$PWD/../QtZKP
DEPENDPATH += $$PWD/../QtZKP

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZKPDummy/release/ -lZKPDummy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZKPDummy/debug/ -lZKPDummy
else:unix: LIBS += -L$$OUT_PWD/../ZKPDummy/ -lZKPDummy

INCLUDEPATH += $$PWD/../ZKPDummy
DEPENDPATH += $$PWD/../ZKPDummy

unix|win32: LIBS += -lcrypto++

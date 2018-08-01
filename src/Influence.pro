#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T15:44:11
#
#-------------------------------------------------

QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Influence
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    kernel/network.cpp \
    kernel/handler.cpp \
    chatwindow.cpp

HEADERS += \
    kernel/network.hpp \
    mainwindow.h \
    kernel/handler.hpp \
    chatwindow.hpp

FORMS += \
        mainwindow.ui \
    chatwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/material-widgets/release/ -lcomponents
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/material-widgets/debug/ -lcomponents
else:unix: LIBS += -L$$PWD/material-widgets/ -lcomponents

INCLUDEPATH += $$PWD/material-widgets
DEPENDPATH += $$PWD/material-widgets

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/material-widgets/release/libcomponents.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/material-widgets/debug/libcomponents.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/material-widgets/release/components.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/material-widgets/debug/components.lib
else:unix: PRE_TARGETDEPS += $$PWD/material-widgets/libcomponents.a

RESOURCES += \
    material-widgets/resources.qrc

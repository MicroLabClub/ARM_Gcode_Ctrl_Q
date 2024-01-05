QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/core\ars.cpp \
    sources/core/workers/fileworker.cpp \
    sources/core/workers/stdworker.cpp \
    sources/core/workers/jogworker.cpp \
    sources/core/workers/teachworker.cpp \
    main.cpp \
    mainwindow.cpp \
    sources/gui_components/LedIndicator/LedIndicator.cpp \

HEADERS += \
    sources/core/ars.h \
    sources/core/workers/fileworker.h \
    sources/core/workers/stdworker.h \
    sources/core/workers/jogworker.h \
    sources/core/workers/teachworker.h \
    mainwindow.h \
    sources/gui_components/LedIndicator/LedIndicator.h \

FORMS += \
    mainwindow.ui

CONFIG(release, debug|release) {
    win32 {
        LIBS += -L$$PWD/libs/Win32/release -lArsCore
        LIBS += -L$$PWD/libs/Win32/release -lArsCoreJoystick
        INCLUDEPATH += $$PWD/libs/Win32/release
        DEPENDPATH += $$PWD/libs/Win32/release
    }
}

CONFIG(debug, debug|release) {
    win32 {
        LIBS += -L$$PWD/libs/Win32/debug -lArsCore
        LIBS += -L$$PWD/libs/Win32/debug -lArsCoreJoystick
        INCLUDEPATH += $$PWD/libs/Win32/debug
        DEPENDPATH += $$PWD/libs/Win32/debug
    }
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

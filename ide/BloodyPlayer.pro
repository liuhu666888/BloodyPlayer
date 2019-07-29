#-------------------------------------------------
#
# Project created by QtCreator 2019-07-25T16:57:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BloodyPlayer
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

CONFIG += c++11

SOURCES += \
        ../src/Controller/controller.cpp \
        ../src/Model/AudioService/audioservice.cpp \
        ../src/Model/Track/track.cpp \
        ../src/View/TrackList/tracklist.cpp \
        ../src/View/TrackWidget/trackwidget.cpp \
        ../src/View/WaitWindow/waitwindow.cpp \
        ../src/main.cpp \
        ../src/View/MainWindow/mainwindow.cpp

HEADERS += \
        ../src/Controller/controller.h \
        ../src/Model/AudioService/audioservice.h \
        ../src/Model/Track/track.h \
        ../src/View/MainWindow/mainwindow.h \
        ../src/View/TrackList/tracklist.h \
        ../src/View/TrackWidget/trackwidget.h \
        ../src/View/WaitWindow/waitwindow.h \
        ../src/globalparams.h

FORMS += \
        ../src/View/MainWindow/mainwindow.ui \
        ../src/View/TrackList/tracklist.ui \
        ../src/View/TrackWidget/trackwidget.ui \
        ../src/View/WaitWindow/waitwindow.ui

LIBS += -L"D:\Program Files (x86)\FMOD Studio API Windows\api\core\lib\x64"


win32
{
    RC_FILE += ../res/rec_file.rc
    OTHER_FILES += ../res/rec_file.rc
}

RESOURCES += ../res/qt_rec_file.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    SecondDownloader_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
SUBDIRS = librarys/libmainwindow
CONFIG(debug,debug|release){
    DESTDIR = ../temp/bin/debug
}else{
    DESTDIR = ../temp/bin/release
}


win32:MOC_DIR = ../temp/moc

win32:OBJECTS_DIR = ../temp/o
win32:UI_DIR = ../temp/ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

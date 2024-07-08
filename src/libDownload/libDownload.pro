QT += widgets gui

TEMPLATE = lib
DEFINES += LIBDOWNLOAD_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    include/libdownload.cpp

HEADERS += \
    include/libDownload_global.h \
    include/libdownload.h
TARGET

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
CONFIG(debug,debug|release){
    DESTDIR = ../temp/bin/
}else{
    DESTDIR = ../temp/bin/
}
win32:MOC_DIR = ../temp/libdownload/moc

win32:OBJECTS_DIR = ..//libdownload/temp/o
win32:UI_DIR = ..//libdownload/temp/ui
win32:LIBS += -luxtheme
INCLUDEPATH +=$$PWD/libcurl/Libcurl
LIBS += $$PWD/libcurl/lib/libcurl.lib

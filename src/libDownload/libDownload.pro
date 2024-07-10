QT += widgets gui

LIBS += -lshell32
QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
TEMPLATE = lib
DEFINES += LIBDOWNLOAD_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    include/downloadmessagewindow.cpp \
    include/downloadwindow.cpp \
    include/libdownload.cpp \
    include/newdownloadwindow.cpp

HEADERS += \
    Style.h \
    include/downloadmessagewindow.h \
    include/downloadwindow.h \
    include/libDownload_global.h \
    include/libdownload.h \
    include/newdownloadwindow.h
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
    DESTDIR = $$PWD/../temp/bin/debug
}else{
    DESTDIR = $$PWD/../temp/bin/release
}
win32:MOC_DIR = $$PWD/../temp/libdownload/moc

win32:OBJECTS_DIR = $$PWD/../temp/libdownload/o
win32:UI_DIR = $$PWD/../temp/libdownload/ui
win32:LIBS += -luxtheme

INCLUDEPATH +=$$PWD/../libDialog
INCLUDEPATH +=$$PWD/include/curl
LIBS+=$$PWD/libcurl/lib/libcurl.lib

CONFIG(debug,debug|release){
   LIBS +=$$PWD/../temp/bin/debug/libDialog.lib
}else{
     LIBS +=$$PWD/../temp/bin/release/libDialog.lib
}
FORMS += \
    include/downloadmessagewindow.ui \
    include/downloadwindow.ui \
    include/newdownloadwindow.ui

RESOURCES += \
    res/res.qrc

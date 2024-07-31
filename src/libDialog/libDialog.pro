QT += widgets

TEMPLATE = lib
DEFINES += LIBDIALOG_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogabout.cpp \
    libdialog.cpp   \
    dialogquestion.cpp  \
    dialogcrtinf.cpp

HEADERS += \
    dialogabout.h \
    libDialog_global.h \
    libdialog.h \
    RadiusFramelessDialog.h \
    Style.h \
    dialogquestion.h    \
    dialogcrtinf.h
FORMS   +=\
    dialogabout.ui \
    dialogquestion.ui   \
    dialogcrtinf.ui

TRANSLATIONS += \
    Translations/LibDialog_zh_TW.ts \
    Translations/LibDialog_zh_CN.ts   \
    Translations/LibDialog_en_US.ts
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
win32:MOC_DIR = $$PWD/../temp/libDialog/moc

win32:OBJECTS_DIR = $$PWD/../temp/libDialog/o
win32:UI_DIR = $$PWD/../temp/libDialog/ui
win32:LIBS += -luxtheme

RESOURCES += \
    res.qrc

TRANSLATIONS +=

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/frmdonate.cpp \
    cpp/frmdownloadcontent.cpp \
    cpp/frmmainpage.cpp \
    cpp/frmsettings.cpp \
    cpp/main.cpp \
    cpp/mainwindow.cpp \
    cpp/dialogquestion.cpp

HEADERS += \
    header/RadiusFramelessDialog.h \
    header/mainwindow.h \
    header/frmdonate.h \
    header/frmdownloadcontent.h \
    header/frmmainpage.h \
    header/frmsettings.h \
    header/Style.h \
    header/dialogquestion.h
FORMS += \
    ui/dialogquestion.ui \
    ui/mainwindow.ui \
    ui/frmdonate.ui \
    ui/frmdownloadcontent.ui \
    ui/frmmainpage.ui \
    ui/frmsettings.ui \
    ui/mainwindow_copy.ui

TRANSLATIONS += \
    SecondDownloader_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
# CONFIG(debug,debug|release){
#     DESTDIR = ../temp/bin/debug
# }else{
#     DESTDIR = ../temp/bin/release
# }


# win32:MOC_DIR = ../temp/moc

# win32:OBJECTS_DIR = ../temp/o
# win32:UI_DIR = ../temp/ui
# win32:LIBS += -luxtheme
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

RESOURCES += \
    qrc/qss.qrc

DISTFILES += \
    res/Donate.png \
    res/Download-Content.png \
    res/Main-Page.png \
    res/Menu.png \
    res/PSD/Donate.psd \
    res/PSD/Download-Content.psd \
    res/PSD/Main-Page.psd \
    res/PSD/Menu.psd \
    res/PSD/Settings.psd \
    res/Settings.png \

RC_ICONS=qrc/res/icon.ico

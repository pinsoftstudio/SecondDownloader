QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    frmdonate.cpp \
    frmdownloadcontent.cpp \
    frmmainpage.cpp \
    frmsettings.cpp \
    main.cpp \
    mainform.cpp \
    stackedwidgetadapter.cpp \
    windowsizeadapter.cpp

HEADERS += \
    frmdonate.h \
    frmdownloadcontent.h \
    frmmainpage.h \
    frmsettings.h \
    mainform.h \
    stackedwidgetadapter.h \
    windowsizeadapter.h

FORMS += \
    frmdonate.ui \
    frmdownloadcontent.ui \
    frmmainpage.ui \
    frmsettings.ui \
    mainform.ui

TRANSLATIONS += \
    SecondDownloader_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
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

RESOURCES += \
    qss.qrc

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
    res/主页/多功能.psd

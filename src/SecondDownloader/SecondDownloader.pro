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
 \    # cpp/dialogquestion.cpp
    cpp/propertydialog.cpp

HEADERS += \
    # header/RadiusFramelessDialog.h \
    header/main.h \
    header/mainwindow.h \
    header/frmdonate.h \
    header/frmdownloadcontent.h \
    header/frmmainpage.h \
    header/frmsettings.h \
    header/Style.h \
 \    # header/dialogquestion.h
    header/propertydialog.h

FORMS += \
    # ui/dialogquestion.ui \
    ui/propertydialog.ui \
    ui/mainwindow.ui \
    ui/frmdonate.ui \
    ui/frmdownloadcontent.ui \
    ui/frmmainpage.ui \
    ui/frmsettings.ui \


TRANSLATIONS += \
    SecondDownloader_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

SUBDIRS+=subProject/libDownload/libDownload
CONFIG(debug,debug|release){
   LIBS +=$$PWD/../temp/bin/debug/libDialog.lib
}else{
     LIBS +=$$PWD/../temp/bin/release/libDialog.lib
}
CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../temp/bin/debug
}else{
    DESTDIR = $$PWD/../temp/bin/release
}


win32:MOC_DIR = $$PWD/../temp/SecondDownloader/moc

win32:OBJECTS_DIR =$$PWD/../temp/SecondDownloader/o
win32:UI_DIR = $$PWD/../temp/SecondDownloader/ui
win32:LIBS += -luxtheme
INCLUDEPATH +=$$PWD/../libDialog
INCLUDEPATH +=$$PWD/../libDownload/include
CONFIG(debug,debug|release){
   LIBS +=$$PWD/../temp/bin/debug/libDownload.lib
}else{
     LIBS +=$$PWD/../temp/bin/release/libDownload.lib
}

# LIBS +=../temp/bin/libDownload.lib
# LIBS +=$$PWD/../temp/bin
#Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
win32:target.path=../build/bin
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


QMAKE_TARGET_COMPANY = "Pinsoft Studio"

# 产品名称
QMAKE_TARGET_PRODUCT = "SecondDownloader"

# 文件说明
QMAKE_TARGET_DESCRIPTION = "SecondDownloader"

# # 版权信息
QMAKE_TARGET_COPYRIGHT = "Copyright© 2024 Pinsoft Studio,org. All rights reserved."

# 中文（简体）
RC_LANG = 0x0004

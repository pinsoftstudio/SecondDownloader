#ifndef STYLE_H
#define STYLE_H

#include <QFile>
#include <QSettings>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QDebug>

static void setCommonStyle()
{
    QApplication *qapp;
    QSettings settings("Pinsoft","SecondDownloader");
    bool isDark=0;
    if(settings.value("Style/FollowSystem",1).toBool()){
        QSettings sysTheme("Microsoft","Windows");
        isDark=(!sysTheme.value("CurrentVersion/Themes/Personalize/AppsUseLightTheme").toBool());
    }else{
        isDark=settings.value("Style/isDark",0).toBool();
    }
    QFile qssFile;
    if(isDark){
        qssFile.setFileName(":/common/qss/dark_base.qss");
    }else{
        qssFile.setFileName(":/common/qss/white_base.qss");
    }
    qssFile.open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile.readAll());
    qssFile.close();
    qapp->setStyleSheet(styleSheet);


}
static void changeDark(bool toDark){

    QSettings settings("Pinsoft","SecondDownloader");
    if(toDark){
        settings.setValue("Style/isDark",1);
    }else{
        settings.setValue("Style/isDark",0);
    }
    setCommonStyle();

}

static  bool isDark(){
    QSettings settings("Pinsoft","SecondDownloader");
    if(settings.value("Style/FollowSystem",1).toBool()){
        QSettings sysTheme("Microsoft","Windows");
        bool isLight=sysTheme.value("CurrentVersion/Themes/Personalize/AppsUseLightTheme").toBool();
        return (!isLight);
    }else{
        return settings.value("Style/isDark",0).toBool();
    }

}
#endif // STYLE_H

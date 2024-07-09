#include <QFile>
#include <QSettings>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QList>
#include <QDebug>
static bool dark;
static QList<QWidget*> w;
static bool getIsDark();
static QApplication *qapp;
static bool getIsDark(){
    return dark;
}

static void setCommonStyle()
{

    QSettings settings("Pinsoft","SecondDownloader");
    bool isDark=0;
    //QString rootReg="HKEY_LOCAL_MACHINE/SOFTWARE/Pinsoft/";
    // QMessageBox::information(this,QString::asprintf(rooReg.toLocal8Bit(),"%sSecondDownloader/Style/isDark"),QString::asprintf(rooReg.toLocal8Bit()));
    isDark=settings.value("Style/isDark",0).toBool();
    qDebug()<<isDark;
    QFile qssFile;
    if(isDark){
        qssFile.setFileName(":/common/qss/dark_base.qss");
    }else{
        qssFile.setFileName(":/common/qss/white_base.qss");
    }
    dark=isDark;
    qssFile.open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile.readAll());
    qssFile.close();
    qapp->setStyleSheet(styleSheet);


}
static void setThisStyle()
{
    setCommonStyle();



    foreach (QWidget *aw, w) {
        QString windowName=aw->metaObject()->className();
        QFile qssFile;
        if(dark){
            qssFile.setFileName(QStringLiteral(":/surface/qss/dark_%1.qss").arg(windowName));
        }else{
            qssFile.setFileName(QStringLiteral(":/surface/qss/white_%1.qss").arg(windowName));
        }
        qssFile.open(QIODevice::ReadOnly);
        QString styleSheet=QString::fromLatin1(qssFile.readAll());
        qssFile.close();
        aw->setStyleSheet(styleSheet);



    }



}

static void addToStyleControl(QWidget *widget){

    w.append(widget);
}

static void changeDark(bool toDark){
    QSettings settings("Pinsoft","SecondDownloader");
    if(toDark){
        settings.setValue("Style/isDark",1);
    }else{
        settings.setValue("Style/isDark",0);
    }
    setThisStyle();

}

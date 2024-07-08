#include <QOperatingSystemVersion>
#include <QSettings>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <header/mainwindow.h>
#include <header/Style.h>
#include <header/dialogquestion.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SecondDownloader_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // QSettings settings("Pinsoft","SecondDownloader");
    // bool isDark=0;
    // //QString rootReg="HKEY_LOCAL_MACHINE/SOFTWARE/Pinsoft/";
    // // QMessageBox::information(this,QString::asprintf(rooReg.toLocal8Bit(),"%sSecondDownloader/Style/isDark"),QString::asprintf(rooReg.toLocal8Bit()));
    // isDark=settings.value("Style/isDark",0).toBool();
    // qDebug()<<isDark;
    // QFile qssFile;
    // if(isDark){
    //     qssFile.setFileName(":/common/qss/white_base.qss");


    // }else{
    //      qssFile.setFileName(":/common/qss/white_base.qss");


    // }
    // qssFile.open(QIODevice::ReadOnly);
    // QString styleSheet=QString::fromLatin1(qssFile.readAll());
    // qssFile.close();
    // a.setStyleSheet(styleSheet);
    setCommonStyle();

    MainWindow w;
    w.show();


    return a.exec();
}

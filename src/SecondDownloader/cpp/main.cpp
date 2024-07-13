#include <QOperatingSystemVersion>
#include <QSettings>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include "header/mainwindow.h"
#include "header/Style.h"
// #include "header/dialogquestion.h"
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
    setCommonStyle();

    MainWindow w;
    w.show();


    return a.exec();
}

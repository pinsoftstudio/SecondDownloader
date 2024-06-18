#include "header/frmmainpage.h"
#include "ui_frmmainpage.h"
#include <QSettings>
#include <QFile>
#include <QDate>
#include <QObject>
frmMainPage::frmMainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmMainPage)
{
    ui->setupUi(this);
    qint64 days=getInstalledDays();
    ui->labMain->setText(tr("已接管下载任务 %1 天").arg(days+1));
}

frmMainPage::~frmMainPage()
{
    delete ui;
}

void frmMainPage::setDark(bool isDark)
{
    QFile qssFile(this);
    if(isDark)
        qssFile.setFileName(":/frmmain/qss/dark_frmmain.qss");
    else
        qssFile.setFileName(":/frmmain/qss/white_frmmain.qss");
    qssFile.open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile.readAll());
    qssFile.close();
    setStyleSheet(styleSheet);
    Dark=isDark;
}

qint64 frmMainPage::getInstalledDays()
{
    QSettings settings("Pinsoft","SecondDownloader");
    qint64 downloadedDates=0;
    QDate curDate=QDate::currentDate();
    //QString rootReg="HKEY_LOCAL_MACHINE/SOFTWARE/Pinsoft/";
    // QMessageBox::information(this,QString::asprintf(rooReg.toLocal8Bit(),"%sSecondDownloader/Style/isDark"),QString::asprintf(rooReg.toLocal8Bit()));
    QDate date=QDate::fromString(settings.value("Common/InstalledDate",curDate.toString()).toString());
    if (date==curDate){
        settings.setValue("Common/InstalledDate",curDate.toString());
    }
    downloadedDates=date.daysTo(curDate);
    return downloadedDates;
}




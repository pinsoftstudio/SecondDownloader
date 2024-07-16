#include "header/frmmainpage.h"
#include "ui_frmmainpage.h"
#include <QSettings>
#include <QFile>
#include <QDate>
#include <QObject>
#include "header/Style.h"
// #include "header/dialogquestion.h"
#include <newdownloadwindow.h>
#include "header/mainwindow.h"

frmMainPage::frmMainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmMainPage)
{

    ui->setupUi(this);

    qint64 days=getInstalledDays();
    ui->labMain->setText(tr("已接管下载任务 %1 天").arg(days+1));
    iniControl();


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

void frmMainPage::iniControl()
{
    QSettings settings("Pinsoft","SecondDownloader");
    bool stopped;
    stopped=settings.value("stopped",0).toBool();
    if(!stopped){
        ui->pushButton->setText("暂停接管(不建议)");
        ui->labpic->setPixmap(QPixmap(":/frmmain/res/started.png"));
        ui->labtxt->setText("SecondDownloader 正在接管您电脑的下载任务");

        settings.setValue("stopped",0);
        //其他操作...
    }else {
        ui->pushButton->setText("继续接管(建议)");
        ui->labpic->setPixmap(QPixmap(":/frmmain/res/warning.png"));
        ui->labtxt->setText("SecondDownloader 已经暂停接管");
        settings.setValue("stopped",1);
        //其他操作...
    }
    ui->pushButton->setChecked(!stopped);

}

void frmMainPage::closeEvent(QCloseEvent *event)
{
    event->accept();
}






void frmMainPage::on_pushButton_clicked(bool checked)
{
    QSettings settings("Pinsoft","SecondDownloader");
    if(checked){
        ui->pushButton->setText("暂停接管(不建议)");
        ui->labtxt->setText("SecondDownloader 正在接管您电脑的下载任务");
        ui->labpic->setPixmap(QPixmap(":/frmmain/res/started.png"));
        settings.setValue("stopped",0);
        //其他操作...
    }else {
        ui->pushButton->setText("继续接管(建议)");
        ui->labtxt->setText("SecondDownloader 已经暂停接管");
         ui->labpic->setPixmap(QPixmap(":/frmmain/res/warning.png"));
        settings.setValue("stopped",1);
        //其他操作...
    }
}


void frmMainPage::on_toolNew_clicked()
{
    newDownload=new NewDownloadWindow;
    newDownload->show();
    connect(newDownload,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(ondownloadThreadExist(DownloadWindow*)));
}






void frmMainPage::on_toolAll_clicked()
{
    emit requestPage(1,0);
}


void frmMainPage::on_toolSuc_clicked()
{
    emit requestPage(1,2);
}


void frmMainPage::on_toolDownloading_clicked()
{
    emit requestPage(1,1);
}


void frmMainPage::on_toolFailed_clicked()
{
    emit requestPage(1,3);
}


void frmMainPage::on_toolExtention_clicked()
{
    //require
}


void frmMainPage::on_toolDonate_clicked()
{
    emit requestPage(2);
}


void frmMainPage::on_toolAbout_clicked()
{

}


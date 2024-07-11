#include "downloadwindow.h"
#include "ui_downloadwindow.h"
// #include <curl.h>
#include <Style.h>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QRandomGenerator>
#include <QTime>
#include <QString>
#include <QDebug>
#include <dialogcrtinf.h>
DownloadWindow::DownloadWindow(QString url,QString saveFileName,qint64 totalBytes,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadWindow)
{
    URL=url;
    savedFilename=saveFileName;
    TotalBytes=totalBytes;

    qDebug()<<TotalBytes;
    ui->setupUi(this);
    {
        progressbar[0]=ui->mainProgress_2;
        progressbar[1]=ui->mainProgress_3;
        progressbar[2]=ui->mainProgress_4;
        progressbar[3]=ui->mainProgress_5;
        progressbar[4]=ui->mainProgress_6;
        progressbar[5]=ui->mainProgress_7;
        progressbar[6]=ui->mainProgress_8;
        progressbar[7]=ui->mainProgress_9;

    }
    ui->laburl->setText(QStringLiteral("URL: %1").arg(URL));
    addToStyleControl(this);
    setThisStyle();
    // curl_global_init(CURL_GLOBAL_ALL);
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    // downloader=new LibDownload
    startDownload();

}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::startDownload()
{
    tempPath=QStandardPaths::writableLocation(QStandardPaths::TempLocation)+"/"+randomPath()+"/";
    QDir mkpth(tempPath);
    if(!mkpth.exists()){
        if( mkpth.mkpath(tempPath)){
            qDebug()<<tempPath;
        };
    }
    tmGetProgress=new QTimer;
    tmsetMainProgress=new QTimer;
    if(TotalBytes>=9){
        isMultipal=true;
        qint64 mod=TotalBytes%8;
        qint64 commonToDownload=(TotalBytes-mod)/8;
        qint64 lastToDownload=commonToDownload+mod;
        qint64 startBytes=0;

        for(int i=0;i<7;i++){
            tempFilePathNames.append(tempPath+randomPath()+".downloading");
            qint64 endBytes=startBytes+commonToDownload;
            qDebug()<<"CNBegin";
            downloaders[i]=new LibDownload(QString::number(startBytes+1),QString::number(endBytes),
                                             QDir::toNativeSeparators(tempFilePathNames[i]),URL,this);
            connect(downloaders[i],&LibDownload::started,this,&DownloadWindow::ondownloadFailed);
            connect(downloaders[i],&LibDownload::finished,this,&DownloadWindow::ondownloadFinished);
            startBytes=endBytes;
            downloaders[i]->start();

        }
        tempFilePathNames.append(tempPath+randomPath()+".downloading");
        downloaders[7]=new LibDownload(QString::number(startBytes+1),"",
                                         QDir::toNativeSeparators(tempFilePathNames[7]),URL,this);
        connect(downloaders[7],&LibDownload::started,this,&DownloadWindow::ondownloadFailed);
        connect(downloaders[7],&LibDownload::finished,this,&DownloadWindow::ondownloadFinished);
         downloaders[7]->start();



            // downloaders.at(7)->start();
    }else{
        isMultipal=false;

    }
    connect(tmsetMainProgress,&QTimer::timeout,this,&DownloadWindow::onsetMainProgress);
    connect(tmGetProgress,&QTimer::timeout,this,&DownloadWindow::ontmGetProgress);
    tmGetProgress->start(50);
    tmsetMainProgress->start(250);
    ui->labstate->setText(tr("正在下载..."));



}

QString DownloadWindow::randomPath()
{
    QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&()_+`-=;',");
    QString randomString;
   for(int i = 0; i < 12; ++i) {
       int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
       randomString.append(possibleCharacters.at(index));
   }
    return QApplication::applicationName()+"-"+randomString;

}

void DownloadWindow::ondownloadThreadExist(DownloadWindow *download)
{

}

void DownloadWindow::ondownloadFailed()
{
    // DialogCrtInf crtInf;
    // QString title="错误";
    // QString text="下载失败！";
    // crtInf.setTitle(title);
    // crtInf.setText(text);
    // crtInf.exec();
}
void DownloadWindow::ondownloadFinished()
{
    if(isMultipal){

    }
}

void DownloadWindow::ontmGetProgress()
{
    if(isMultipal){
        for(int i=0;i<8;i++){
            double  now=0;
            double total=0;
            downloaders[i]->getDownloadProgress(now,total);
            downloaded[i]=static_cast<qint64>(now);
            progressbar[i]->setMaximum(static_cast<qint64>(total));
            progressbar[i]->setValue(downloaded[i]);
            // downloadedBytes+=now;


        }
    }
}

void DownloadWindow::onsetMainProgress(){
    if(isMultipal){
        qint64 totalDownloaded=0;
        for(int i=0;i<8;i++){
            totalDownloaded+=downloaded[i];
             ui->mainProgress->setMaximum(TotalBytes);
            ui->mainProgress->setValue(totalDownloaded);
        }
        nowDownloaded=totalDownloaded;
        qint64 thisDownloaded=nowDownloaded-lastDownloaded;
        if(thisDownloaded>0){
            long double speed=thisDownloaded/1024.00/1024.00*4;
            QString str;
            if(speed>=1){
                str=tr("正在下载...( %1 MB/s)");
                // ui->label->setText(str.arg("正在下载...").arg(speed, 0, 'f', 2));
            }else if(speed*1024>=1){
                speed=thisDownloaded/1024*12.5;
                str=tr("正在下载...( %1 KB/s)");
                // ui->label->setText(str.arg("正在下载...").arg(speed, 0, 'f', 2));
            }else if(speed>=1){
                speed=thisDownloaded*12.5;
                str=tr("正在下载...( %1 B/s)");
                // ui->label->setText(str.arg("正在下载...").arg(speed, 0, 'f', 2));
            }
            ui->labstate->setText(str.arg(speed, 0, 'f', 2));
        }
        lastDownloaded=nowDownloaded;
    }

}


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
#include <QWidget>
#include "dialogdownloaded.h"
#include "dialogcrtinf.h"
#include <QBuffer>
#include <iostream>
#include <QThread>
#include <QMessageBox>
#include <QMutex>
#include "analyserresult.h"
#include "QSoundEffect"
#include "QDesktopServices"

DownloadWindow::DownloadWindow(QString url,QString saveFileName,qint64 totalBytes,QMap<QString,QString>mapCookies,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadWindow)
{
    URL=url;
    savedFilename=saveFileName;
    cookieMap=mapCookies;
    TotalBytes=totalBytes;
    iniSharedMemory();  //初始化共享内存

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


    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);

    // setAttribute(Qt::WA_DeleteOnClose);
    startDownload();

    //开始向“下载内容”发送下载信息
    tmsendMemory=new QTimer;
    connect(tmsendMemory,&QTimer::timeout,this,&DownloadWindow::onsendMemory);
    tmsendMemory->start(50);
    if(isDark()){
        setStyleSheet("#DownloadWindow{"
                      "background-color:rgb(30,30,30)}");
        ui->labbytes->setStyleSheet(
                      "background-color:rgb(30,30,30)}");
        ui->label->setStyleSheet(
            "{background-color:rgb(30,30,30)}");
        ui->labstate->setStyleSheet(
            "{background-color:rgb(30,30,30)}");
        ui->laburl->setStyleSheet(
            "{background-color:rgb(30,30,30)}");
    }else {
        setStyleSheet("#DownloadWindow{"
                      "background-color:white}");
        ui->label->setStyleSheet(
            "{background-color:white}");
        ui->labstate->setStyleSheet(
            "{background-color:white}");
        ui->laburl->setStyleSheet(
            "{background-color:white}");
    }


}

DownloadWindow::~DownloadWindow()
{
    cleanup();
    delete ui;


}

void DownloadWindow::iniSharedMemory()
{
    qDebug()<<"head";

    //获取共享内存密钥
    key=randomPath();
    long  double totals=TotalBytes;
    QString unit;
    getSuitableUnit(totals,unit);

    share=new QSharedMemory(key);
    qDebug()<<"passkey:"<<key;

    //连接到共享内存
    if(!share->create(4096)){
        if(share->attach()){
            qDebug()<<"share attached";
        }else{
            qDebug()<<"share attached error";
             return;
        }
    }
    if(!share->lock()){
        qDebug()<<"Lock share memory error.";
        return;
    }

    //映射内存
    char* to=static_cast<char*>(share->data());
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QDataStream stream(&buffer);

    //更新状态为“准备下载”
    state="pre";
    stream<<savedFilename<<URL<<state<<QStringLiteral("%1 %2").arg(totals,0,'f',2).arg(unit)<<strspeed;

    //拷贝内存
    memcpy(to,buffer.data().data(),buffer.size());
    share->unlock();



    //初始化传输下载信息的共享内存对象
    passKey=new QSharedMemory("passkey");
    if(!passKey->create(1024)){
        qDebug()<<"Create passKey memory error.";
        passKey->attach();

    }

    //尝试锁上代码块
    link:
    if(!passKey->lock()){
            QThread::msleep(1000);
        qDebug()<<"Lock passKey memory error.";
            goto link;
    }

    char *toKey=static_cast<char*>(passKey->data());
    QBuffer keyBuffer;
    keyBuffer.open(QBuffer::WriteOnly);
    QDataStream keyStream(&keyBuffer);
    keyStream<<key;

    memcpy(toKey,keyBuffer.data(),keyBuffer.size());
    passKey->unlock();







}

void DownloadWindow::makeAtray()
{
    tray=new QSystemTrayIcon(this);
    trayMenu=new QMenu(this);
    trayMenu->addAction(&actProgress);
    setVisible(0);

    tray->setIcon(QIcon(":/common/res/SecondDownloader-inner.png"));
    connect(&actProgress,&QAction::triggered,this,&DownloadWindow::onMessageClicked);
    tray->setContextMenu(trayMenu);
    tray->show();
    connect(tray,&QSystemTrayIcon::messageClicked,this,&DownloadWindow::onMessageClicked);
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(onTrayActivated(QSystemTrayIcon::ActivationReason)));

    tray->showMessage(tr("下载对话框已隐藏至托盘"),tr("点击我或托盘查看下载进度。"),QSystemTrayIcon::Information);

}

void DownloadWindow::startDownload()
{

    //创建下载临时目录
    tempPath=QStandardPaths::writableLocation(QStandardPaths::TempLocation)+"/"+randomPath()+"/";
    QDir mkpth(tempPath);
    if(!mkpth.exists()){
        if( mkpth.mkpath(tempPath)){
            qDebug()<<tempPath;
        };
    }

    if(TotalBytes>=9){
        isMultipal=true;
        //分配每个线程的下载字节数
        qint64 mod=TotalBytes%8;
        qint64 commonToDownload=(TotalBytes-mod)/8;
        qint64 startBytes=-1;

        //启动每个线程的下载
        for(int i=0;i<7;i++){
            tempFilePathNames.append(tempPath+randomPath()+".downloading");
            qint64 endBytes=startBytes+commonToDownload;
            qDebug()<<"CNBegin";
            if(i==0){
                downloaders[i]=new LibDownload(QString::number(startBytes+1),QString::number(endBytes),
                                                 QDir::toNativeSeparators(tempFilePathNames[i]),URL,1,this,cookieMap);
                connect(downloaders[0],&LibDownload::onlyOne,this,&DownloadWindow::onOnlyOne);
            }else{
                downloaders[i]=new LibDownload(QString::number(startBytes+1),QString::number(endBytes),
                                                 QDir::toNativeSeparators(tempFilePathNames[i]),URL,0,this,cookieMap);
            }

            connect(downloaders[i],&LibDownload::started,this,&DownloadWindow::ondownloadFailed);
            connect(downloaders[i],&LibDownload::finished,this,&DownloadWindow::ondownloadFinished);
            startBytes=endBytes;
            downloaders[i]->start();
        }
        tempFilePathNames.append(tempPath+randomPath()+".downloading");
        downloaders[7]=new LibDownload(QString::number(startBytes+1),"",
                                         QDir::toNativeSeparators(tempFilePathNames[7]),URL,0,this,cookieMap);
        connect(downloaders[7],&LibDownload::started,this,&DownloadWindow::ondownloadFailed);
        connect(downloaders[7],&LibDownload::finished,this,&DownloadWindow::ondownloadFinished);
        downloaders[7]->start();

    }else{
        isMultipal=false;
        tempFilePathNames.append(tempPath+randomPath()+".downloading");
        downloaders[0]=new LibDownload("0","",
                                         QDir::toNativeSeparators(tempFilePathNames[0]),URL,1,this,cookieMap);
        connect(downloaders[0],&LibDownload::started,this,&DownloadWindow::ondownloadFailed);
        connect(downloaders[0],&LibDownload::finished,this,&DownloadWindow::ondownloadFinished);
        downloaders[0]->start();
        ui->frame->hide();
    }

    //启动QTimer来刷新进度条
    tmGetProgress=new QTimer;
    tmsetMainProgress=new QTimer;
    connect(tmsetMainProgress,&QTimer::timeout,this,&DownloadWindow::onsetMainProgress);
    connect(tmGetProgress,&QTimer::timeout,this,&DownloadWindow::ontmGetProgress);
    tmGetProgress->start(50);
    tmsetMainProgress->start(250);

    //改变状态为“正在下载”
    state="downloading";
    ui->labstate->setText(tr("正在下载..."));



}

QString DownloadWindow::randomPath()
{
    QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&()_+`-=;',");
    QString randomString;
    for(int i = 0; i < 12; ++i){
       int index = QRandomGenerator::global()->bounded(possibleCharacters.length());
       randomString.append(possibleCharacters.at(index));
    }
    return QApplication::applicationName()+"-"+randomString;

}

void DownloadWindow::getSuitableUnit(long double &bytes, QString &unit)
{
    long double tempBytes=0;
    if(bytes>=1024*1024*1024){
        tempBytes=bytes/1024.00/1024.00/1024.00;

        unit="GB";
    }else if(bytes>=1024*1024){
        tempBytes=bytes/1024.00/1024.00;
        unit="MB";
    }else if(bytes>=1024){
        tempBytes=bytes/1024.00;
        unit="KB";
    }else {
        tempBytes=bytes;
        unit="B";
    }
    bytes=tempBytes;
}

void DownloadWindow::closeEvent(QCloseEvent *event)
{
    if(needtoclose){
        //如果需要关闭窗口
        event->accept();

    }else{
        makeAtray();
         event->ignore();
    }

}

void DownloadWindow::cleanup()
{
    if(isMultipal){
        //彻底停止更新进度条

        disconnect(tmsetMainProgress,&QTimer::timeout,this,&DownloadWindow::onsetMainProgress);
        disconnect(tmGetProgress,&QTimer::timeout,this,&DownloadWindow::ontmGetProgress);
        if(tmsetMainProgress->isActive()){
            tmGetProgress->stop();
        }

        if(tmGetProgress->isActive()){
            tmsetMainProgress->stop();
        }


        //如果每个线程还未完全停止，就强制结束线程
        for(int i=0;i<8;i++){
            if(downloaders[i]->isRunning()){
                disconnect(downloaders[i],&LibDownload::started,this,&DownloadWindow::ondownloadFailed);
                disconnect(downloaders[i],&LibDownload::finished,this,&DownloadWindow::ondownloadFinished);
                downloaders[i]->terminate();
                downloaders[i]->wait();
            }
        }
    }

    //彻底停止共享内存
    disconnect(tmsendMemory,&QTimer::timeout,this,&DownloadWindow::onsendMemory);
    if(tmsendMemory->isActive()){
        tmsendMemory->stop();
    }
    if(share->isAttached()){
        share->detach();
    }
    if(passKey->isAttached()){
        passKey->detach();
    }



    //清理临时文件夹
    QDir dir;
    QFileInfo fi(QDir::fromNativeSeparators(savedFilename));
    dir.rmdir(fi.absolutePath());
    passKey->detach();

}



void DownloadWindow::ondownloadFailed()
{
    state="failed";
    //cleanup();

}
void DownloadWindow::ondownloadFinished()
{

    QThread::msleep(100);
    if(isMultipal){
        //统计完成了任务的进程
        finishedThreads++;
        //如果全部完成了
        if(finishedThreads==8){
            for(int i=0;i<8;i++){
                downloaders[i]->terminate();
                downloaders[i]->wait();
                progressbar[i]->setMaximum(100);
                progressbar[i]->setValue(100);
                ui->labbytes->setText(tr("下载状态：全部下载完成！"));

                ui->labstate->setText(tr("下载完成！"));
                setWindowTitle(tr("下载完成！"));
                actProgress.setText(tr("合并文件中..."));
            }

            tmGetProgress->stop();
            tmsetMainProgress->stop();
            disconnect(tmsetMainProgress,&QTimer::timeout,this,&DownloadWindow::onsetMainProgress);
            disconnect(tmGetProgress,&QTimer::timeout,this,&DownloadWindow::ontmGetProgress);
            ui->mainProgress->setValue(0);
            ui->labstate->setText(tr("正在合并为一个文件..."));
            setWindowTitle(tr("正在合并为一个文件..."));
            appender=new fileAppender(savedFilename,this);

            state="succeed";
            strspeed="";
            QThread::msleep(100);

            //开始合并文件
            for(int j=0;j<8;j++){
             appender->addToFileList(tempFilePathNames[j]);
            }
            connect(appender,&fileAppender::appendFailed,this,&DownloadWindow::onAppendFailed);
            connect(appender,&fileAppender::appendSucceed,this,&DownloadWindow::onAppendSucceed);
            connect(appender,SIGNAL(appendProgress(int,int)),this,SLOT(onGetAppendProgress(int,int)));
            appender->start();


        }
    }else{
        downloaders[0]->terminate();
        downloaders[0]->wait();
        ui->labbytes->setText(tr("下载状态：全部下载完成！"));

        ui->labstate->setText(tr("下载完成！"));
        setWindowTitle(tr("下载完成！"));
        actProgress.setText(tr("合并文件中..."));
        tmGetProgress->stop();
        tmsetMainProgress->stop();
        disconnect(tmsetMainProgress,&QTimer::timeout,this,&DownloadWindow::onsetMainProgress);
        disconnect(tmGetProgress,&QTimer::timeout,this,&DownloadWindow::ontmGetProgress);
        ui->mainProgress->setValue(0);
        ui->labstate->setText(tr("正在合并为一个文件..."));
        setWindowTitle(tr("正在合并为一个文件..."));
        appender=new fileAppender(savedFilename,this);

        state="succeed";



        strspeed="";
        QThread::msleep(100);
        appender->addToFileList(tempFilePathNames[0]);
        connect(appender,&fileAppender::appendFailed,this,&DownloadWindow::onAppendFailed);
        connect(appender,&fileAppender::appendSucceed,this,&DownloadWindow::onAppendSucceed);
        connect(appender,SIGNAL(appendProgress(int,int)),this,SLOT(onGetAppendProgress(int,int)));
        appender->start();

    }
}

void DownloadWindow::ontmGetProgress()
{
    //保护数据
    QMutex m;
    m.lock();
    if(isMultipal){
        for(int i=0;i<8;i++){
            double  now=0;
            double total=0;

            downloaders[i]->getDownloadProgress(now,total);
            //统计每个进程的下载字节数
            downloaded[i]=static_cast<qint64>(now);
            progressbar[i]->setMaximum(static_cast<qint64>(total));
            progressbar[i]->setValue(downloaded[i]);
        }
    }else{
        double  now=0;
        double total=0;
        downloaders[0]->getDownloadProgress(now,total);
        //统计下载字节数
        downloaded[0]=static_cast<qint64>(now);
        ui->mainProgress->setMaximum(static_cast<qint64>(total));
        ui->mainProgress->setValue(downloaded[0]);
    }
    m.unlock();
}

void DownloadWindow::onsetMainProgress(){

    QString temp=downloaders[0]->getTrueFileName();
    if(temp!="" &&(!fileNameGetted)){
        QString savePath=QFileInfo(savedFilename).absolutePath();
        savedFilename=savePath+"/"+temp;
        fileNameGetted=1;
    }
    qDebug()<<savedFilename;
    if(isMultipal){
        QMutex m;
        m.lock();
        qint64 totalDownloaded=0;
        for(int i=0;i<8;i++){
            //计算总下载字节
            totalDownloaded+=downloaded[i];
            ui->mainProgress->setMaximum(TotalBytes);
            ui->mainProgress->setValue(totalDownloaded);

        }
        nowDownloaded=totalDownloaded;
        qint64 thisDownloaded=nowDownloaded-lastDownloaded;
        QString tempspeed;
        if(thisDownloaded>0){
            //计算下载速度
            long double speed=thisDownloaded/1024.00/1024.00*4.00;
            QString str;
            state="downloading";
            if(speed>=1){
                str=tr("正在下载...( %1 MB/s)");
                tempspeed=QStringLiteral("%1 MB/s");
            }else if(speed*1024>=1){
                speed=thisDownloaded/1024.00*4.00;
                str=tr("正在下载...( %1 KB/s)");
                tempspeed=QStringLiteral("%1 KB/s");
            }else if(speed>=1){
                speed=thisDownloaded*4.00;
                str=tr("正在下载...( %1 B/s)");
                tempspeed=QStringLiteral("%1 B/s");
            }
            ui->labstate->setText(str.arg(speed, 0, 'f', 2));
            strspeed=tempspeed.arg(speed, 0, 'f', 2);
        }
            lastDownloaded=nowDownloaded;
            long double downloaded=nowDownloaded;
            long double totals=TotalBytes;
            QString totalunit="";
            QString downloadedunit="";
            getSuitableUnit(downloaded,downloadedunit);
            getSuitableUnit(totals,totalunit);
            actProgress.setText(tr("下载状态：%1 %2/%3 %4").arg(downloaded,0, 'f', 2).arg(downloadedunit).arg(totals,0, 'f', 2).arg(totalunit));
            ui->labbytes->setText(tr("下载状态：%1 %2/%3 %4").arg(downloaded,0, 'f', 2).arg(downloadedunit).arg(totals,0, 'f', 2).arg(totalunit));


            // if(tray!=Q_NULLPTR){
            //     tray->setToolTip(tr("下载状态：%1 %2/%3 %4").arg(downloaded,0, 'f', 2).arg(downloadedunit).arg(totals,0, 'f', 2).arg(totalunit));
            // }


     m.unlock();
    }else{
        qint64 totalDownloaded=0;
        totalDownloaded=downloaded[0];
        nowDownloaded=totalDownloaded;
        qint64 thisDownloaded=nowDownloaded-lastDownloaded;
        QString tempspeed;
        if(thisDownloaded>0){
            //计算下载速度
            long double speed=thisDownloaded/1024.00/1024.00*4.00;
            QString str;
            state="downloading";
            if(speed>=1){
                str=tr("正在下载...( %1 MB/s)");
                tempspeed=QStringLiteral("%1 MB/s");
            }else if(speed*1024>=1){
                speed=thisDownloaded/1024.00*4.00;
                str=tr("正在下载...( %1 KB/s)");
                tempspeed=QStringLiteral("%1 KB/s");
            }else if(speed>=1){
                speed=thisDownloaded*4.00;
                str=tr("正在下载...( %1 B/s)");
                tempspeed=QStringLiteral("%1 B/s");
            }
            ui->labstate->setText(str.arg(speed, 0, 'f', 2));
            strspeed=tempspeed.arg(speed, 0, 'f', 2);
        }
        lastDownloaded=nowDownloaded;
        long double downloaded=nowDownloaded;
        long double totals=TotalBytes;
        QString totalunit="";
        QString downloadedunit="";
        getSuitableUnit(downloaded,downloadedunit);
        getSuitableUnit(totals,totalunit);
        actProgress.setText(tr("下载状态：%1 %2/%3 %4").arg(downloaded,0, 'f', 2).arg(downloadedunit).arg(totals,0, 'f', 2).arg(totalunit));
        ui->labbytes->setText(tr("下载状态：%1 %2/%3 %4").arg(downloaded,0, 'f', 2).arg(downloadedunit).arg(totals,0, 'f', 2).arg(totalunit));


    }


}

void DownloadWindow::onGetAppendProgress(int now, int total)
{
    // ui->labstate->setText(tr("正在合并为一个文件..."));
    state="succeed";
    strspeed="";
    ui->mainProgress->setMaximum(total);
    ui->mainProgress->setValue(now);
}



void DownloadWindow::onAppendFailed()
{
     ui->labstate->setText(tr("合并失败！"));
      cleanup();

}

void DownloadWindow::onAppendSucceed()
{
    QSettings set("Pinsoft","SecondDownloader");
    state="succeed";
    strspeed="";
    ui->labstate->setText(tr("合并成功！"));
     setWindowTitle(tr("合并成功！"));
    appender->terminate();
    appender->wait();

    QString finishedToDo=set.value("Download/FinishedToDo","ShowDialog").toString();
    if(finishedToDo=="ShowDialog"){
        DialogDownloaded *diadown=new DialogDownloaded;
        diadown->setSavedLocation(savedFilename);
        diadown->show();
    }else if(finishedToDo=="OpenFile"){
        QDesktopServices::openUrl(QUrl(QDir::fromNativeSeparators(savedFilename)));
    }else if(finishedToDo=="OpenFolder"){
        QFileInfo fileinfo(QDir::fromNativeSeparators(savedFilename));
        QString savedFolder=fileinfo.absolutePath();
        QDesktopServices::openUrl(QUrl(savedFolder));
    }else if(finishedToDo=="NotNotice"){
        ;
    }else{

        set.setValue("Download/FinishedToDo","ShowDialog");
    }


    // tmsendMemory->stop();
    // disconnect(tmsendMemory,&QTimer::timeout,this,&DownloadWindow::onsendMemory);
    cleanup();
    needtoclose=1;

    if(set.value("Download/ScanFile",1).toBool()){
        QFileInfo fi(QDir::fromNativeSeparators(savedFilename));
        if((fi.size() <= (1024*1024*32)) && (fi.suffix().toLower()=="exe" ||
                                            fi.suffix().toLower()=="apk" ||
                                            fi.suffix().toLower()=="dmp" ||
                                            fi.suffix().toLower()=="app" ||
                                            fi.suffix().toLower()=="ipa" ||
                                            fi.suffix().toLower()=="run")){
            AnalyserResult *ar=new AnalyserResult(QDir::fromNativeSeparators(savedFilename));
            ar->show();
        }

        if(set.value("Download/FinishBell",0).toBool()){
            QString soundSource=set.value("Download/BellPath","").toString();
            QSoundEffect *sound=new QSoundEffect(this);
            sound->setSource(QUrl::fromLocalFile(soundSource));
            sound->setVolume(1.0);
            sound->play();
        }



    }
    close();

}

void DownloadWindow::onMessageClicked()
{
    delete tray;
    show();
}

void DownloadWindow::onTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger){
        delete tray;
        show();
    }
}

void DownloadWindow::onActionTriggered()
{
    delete tray;
    show();
}





void DownloadWindow::on_btncancel_clicked()
{
    state="failed";
    onsendMemory();
    QThread::msleep(100);
    cleanup();
    needtoclose=1;
    close();
}


void DownloadWindow::on_btnmin_clicked()
{
    makeAtray();
}

void DownloadWindow::onsendMemory()
{
    try{
    long double totals=TotalBytes;
    QString unit;
    getSuitableUnit(totals,unit);
    if(!share->lock()){

        qDebug()<<"Lock share memory error.";
        return;
    }
    char* to=static_cast<char*>(share->data());
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QDataStream stream(&buffer);
    qDebug()<<QStringLiteral("%1 %2").arg(totals,0,'f',2).arg(unit);
    stream<<savedFilename<<URL<<state<<QStringLiteral("%1 %2").arg(totals,0,'f',2).arg(unit)<<strspeed;
    memcpy(to,buffer.data().data(),buffer.size());

        share->unlock();
    }
    catch(...){
        ;
    }
}

void DownloadWindow::onOnlyOne()
{
    if(isMultipal){
        isMultipal=0;
        ui->frame->hide();


    }

}


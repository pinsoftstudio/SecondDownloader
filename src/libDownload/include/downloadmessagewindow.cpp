#include "downloadmessagewindow.h"
#include "ui_downloadmessagewindow.h"

#include "QUrl"
#include "QSettings"
#include "QStandardPaths"
#include "QDir"
#include "dialogcrtinf.h"
#include "QFileIconProvider"
#include "QFileInfo"
#include <Style.h>
#include <QFileDialog>
DownloadMessageWindow::DownloadMessageWindow(QString url, QWidget *lastWindow, bool passedNull, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadMessageWindow)
{
    passedNULL=passedNull;
    if(!passedNull){
        LastWindow=lastWindow;

    }
    URL=url;
    ui->setupUi(this);
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint|Qt::WindowStaysOnTopHint);
    ui->btnStart->setProperty("highlight","true");
    // ui->linelocation->setText(qurl.fileName());

    iniUi();

    FileUrlInfo *urlinfo=new FileUrlInfo(URL);
    // QThread *thread =new QThread;
    // urlinfo->moveToThread(thread);
    connect(urlinfo,SIGNAL(sizeReady(qint64)),this,SLOT(onsizeready(qint64)));
    connect(urlinfo,&FileUrlInfo::UrlReady,this,&DownloadMessageWindow::onurlready);
    connect(urlinfo,SIGNAL(UrlReady(QString)),this,SLOT(onurlready(QString)));
    connect(urlinfo,&FileUrlInfo::getERROR,this,&DownloadMessageWindow::ongeterror);
    // QObject::connect(thread, &QThread::started, [urlinfo](){
    //     urlinfo->getFileSize();
    // });
    QObject::connect(urlinfo, &FileUrlInfo::finished, [urlinfo](){
        urlinfo->deleteLater();

    });
    urlinfo->start();



}

DownloadMessageWindow::~DownloadMessageWindow()
{
    delete ui;
}

void DownloadMessageWindow::iniUi()
{

    ui->lineurl->setText(URL);
    QUrl qurl(URL);
    QString fileName;
    QSettings set("Pinsoft","SecondDownloader");
    if(set.value("Download/SavingLocation/isDefault",1).toBool()==1){
        QString qtSavingLoaction=QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        savingLocation=QDir::toNativeSeparators(qtSavingLoaction);
    }else{
        savingLocation=set.value("Download/SavingLocation/location",
                                   QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)
                                       )).toString();
    }

    if(!QDir(savingLocation).exists()){
        QDir dir;
        if(!dir.mkpath(QDir::fromNativeSeparators(savingLocation))){
            DialogCrtInf criticalBox;
            QString title="错误";
            QString text="创建文件夹失败！请重新选择保存位置！";
            criticalBox.setTitle(title);
            criticalBox.setText(text);
            criticalBox.exec();
            savingLocation=QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
            if(savingLocation.right(1)=="\\"){
                fileName=savingLocation+qurl.fileName();
            }else{
                fileName=savingLocation+"\\"+qurl.fileName();
            }

            savedFileName=fileName;
            ui->linelocation->setText(fileName);
            ui->labIcon->setPixmap(getFilePixmap(fileName));
            return;
        }
    }else{
        if(savingLocation.right(1)=="\\"){
             fileName=savingLocation+qurl.fileName();
        }else{
             fileName=savingLocation+"\\"+qurl.fileName();
        }
        savedFileName=fileName;
        ui->linelocation->setText(fileName);
        ui->labIcon->setPixmap(getFilePixmap(fileName));
    }

}


QPixmap DownloadMessageWindow::getFilePixmap(QString fileLocation)
{
    QFileInfo fi(fileLocation);
    QFileIconProvider provider;
    return provider.icon(fi).pixmap(60,60);
}



void DownloadMessageWindow::onsizeready(qint64 filesize)
{
    size=filesize;
    qint64 calsize;
    if(filesize>0){
        if(filesize>=1024*1024){
            calsize=filesize/1024.00/1024.00;
            finalSize=tr("文件大小： %1 MB").arg(calsize,0,'f',2);
        }else if(filesize>=1024){
            calsize=filesize/1024.00;
            finalSize=tr("文件大小： %1 KB").arg(calsize,0,'f',2);
        }else {
            calsize=filesize;
            finalSize=tr("文件大小： %1 B").arg(calsize,0,'f',2);
        }
        ui->labfilesize->setText(finalSize);
    }else{
        ui->labfilesize->setText("文件大小：未知");
    }
    // URL=finalUrl;
    // ui->lineurl->setText(URL);

    ui->btnStart->setEnabled(1);
}

void DownloadMessageWindow::onurlready(QString finalUrl)
{
    URL=finalUrl;
    ui->lineurl->setText(URL);
    iniUi();
    // iniUi();
}

void DownloadMessageWindow::on_btnStart_clicked()
{
    downloadwindow=new DownloadWindow(URL,savedFileName,size);
    qDebug()<<size;
    connect(downloadwindow,SIGNAL(downloadThreadExist(DownloadWindow*)),SLOT(ondownloadThreadExist(DownloadWindow*)));
    downloadwindow->show();
    close();
    if(!passedNULL){
        LastWindow->close();

    }


}

void DownloadMessageWindow::ongeterror()
{
    ui->labfilesize->setText("文件大小： 未知");
    ui->btnStart->setEnabled(1);
}

void DownloadMessageWindow::on_btnChoose_clicked()
{
    ui->lineurl->setText(URL);
    QUrl qurl(URL);
    QString path;
    QFileInfo file(ui->linelocation->text());
    QString defaultPath=file.filePath();
    path=QFileDialog::getExistingDirectory(this,"选择一个保存位置",defaultPath);
    if(path!=""){
        savingLocation=QDir::toNativeSeparators(path);
        if(savingLocation.right(1)=="\\"){
            savedFileName=QDir::toNativeSeparators(path+qurl.fileName());
        }else{
            savedFileName=QDir::toNativeSeparators(path+"/"+qurl.fileName());
        }
        ui->linelocation->setText(savedFileName);
    }
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/SavingLocation/isDefault",0);
    set.setValue("Download/SavingLocation/location",savingLocation);
}



#include "newdownloadwindow.h"
#include "ui_newdownloadwindow.h"
#include "Style.h"
#include "QUrl"
#include <dialogcrtinf.h>
#include <QClipboard>
#include <QMimeData>
NewDownloadWindow::NewDownloadWindow(QWidget *parent): QWidget(parent)
    , ui(new Ui::NewDownloadWindow)
{
    if(parent!=nullptr)  setParent(this);
     ui->setupUi(this);
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    ui->btnStart->setProperty("highlight","true");
    const QClipboard *clip=QApplication::clipboard();
    const QMimeData *mime=clip->mimeData();
    QUrl url(mime->text());

    if(!url.scheme().isEmpty()){
        ui->lineurl->setText(mime->text());
        ui->lineurl->selectAll();
    }
    setAttribute(Qt::WA_DeleteOnClose);
    if(isDark()){
        this->setStyleSheet("#NewDownloadWindow{background-color:rgb(40,40,40)}");

    }else{
        this->setStyleSheet("#NewDownloadWindow{background-color:rgb(240,240,240)}");
    }


}

NewDownloadWindow::~NewDownloadWindow()
{
    delete ui;
}

QStringList NewDownloadWindow::getNoUseScheme()
{
    QSettings set("Pinsoft","SecondDownloader");
    QStringList returnList;
    if(!set.value("Download/http",1).toBool()){
        returnList.append("http");
    }
    if(!set.value("Download/https",1).toBool()){
        returnList.append("https");
    }
    if(!set.value("Download/ftp",1).toBool()){
        returnList.append("ftp");
    }
    if(!set.value("Download/ftps",1).toBool()){
        returnList.append("ftps");
    }
    if(!set.value("Download/others",1).toBool()){
        returnList.append("others");
    }
    return returnList;
}



void NewDownloadWindow::on_btnStart_clicked()
{
    QString strurl=ui->lineurl->text();
    QUrl url(strurl);

    QStringList list=getNoUseScheme();
    QString urlScheme=url.scheme().toLower();
    bool containsOthers=0;
    foreach (QString aScheme, list) {
        if(aScheme=="others"){
            containsOthers=1;
        }
        if(aScheme==urlScheme){
            DialogCrtInf criticalBox;
            QString title="错误";
            QString text="下载地址不合法或协议被禁用！";
            criticalBox.setTitle(title);
            criticalBox.setText(text);
            criticalBox.exec();
            return;
        }

    }
    bool contained=0;
    if(urlScheme=="https" || urlScheme=="http" || urlScheme=="ftps" || urlScheme=="ftp"){
        contained=1;
    }
    if((containsOthers || urlScheme.isEmpty()) &&(!contained)){
        DialogCrtInf criticalBox;
        QString title="错误";
        QString text="下载地址不合法或协议被禁用！";
        criticalBox.setTitle(title);
        criticalBox.setText(text);
        criticalBox.exec();
        return;
    }

    downloadmessagewindow=new  DownloadMessageWindow(strurl,this,0,nullptr);
    connect(downloadmessagewindow,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(ondownloadThreadExist(DownloadWindow*)));
    downloadmessagewindow->setWindowModality(Qt::ApplicationModal);
    downloadmessagewindow->show();
}


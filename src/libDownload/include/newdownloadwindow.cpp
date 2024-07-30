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
    const QClipboard *clip=QApplication::clipboard();   //获取文本框对象
    const QMimeData *mime=clip->mimeData();
    QUrl url(mime->text()); //用文本框内容构造url对象

    if(!url.scheme().isEmpty() && url.scheme().toLower()+"://"!=url.toString().toLower()){        //如果剪贴板协议头不为空
        ui->lineurl->setText(mime->text());     //粘贴剪贴板文本到文本框中
        ui->lineurl->selectAll();   //全选文本框
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
    QString urlScheme=url.scheme().toLower().trimmed();
    if(urlScheme.isEmpty() || urlScheme+"://"==strurl.trimmed()){
        DialogCrtInf criticalBox;
        QString title="错误";
        QString text="下载地址不合法!";
        criticalBox.setTitle(title);
        criticalBox.setText(text);
        criticalBox.exec();
        return;
    }
    QStringList list=getNoUseScheme();

    bool containsOthers=0;
    foreach (QString aScheme, list) {
        if(aScheme=="others"){
            containsOthers=1;
        }
        if(aScheme==urlScheme){
            DialogCrtInf criticalBox;
            QString title="错误";
            QString text="下载协议被禁用！";
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


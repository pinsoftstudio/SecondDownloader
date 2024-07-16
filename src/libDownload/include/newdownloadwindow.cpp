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


}

NewDownloadWindow::~NewDownloadWindow()
{
    delete ui;
}



void NewDownloadWindow::on_btnStart_clicked()
{
    QString strurl=ui->lineurl->text();
    QUrl url(strurl);

    if(url.scheme().isEmpty()){
        DialogCrtInf criticalBox;
        QString title="错误";
        QString text="下载地址不合法！";
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


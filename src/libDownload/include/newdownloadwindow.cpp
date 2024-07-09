#include "newdownloadwindow.h"
#include "ui_newdownloadwindow.h"
#include "Style.h"
#include "QUrl"
NewDownloadWindow::NewDownloadWindow(QWidget *parent): QWidget(parent)
    , ui(new Ui::NewDownloadWindow)
{
    if(parent!=nullptr)  setParent(this);
     ui->setupUi(this);
    setCommonStyle();
    addToStyleControl(this);
    setThisStyle();
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    ui->btnStart->setProperty("highlight","true");



}

NewDownloadWindow::~NewDownloadWindow()
{
    delete ui;
}

void NewDownloadWindow::ondownloadThreadExist(DownloadWindow *downloadwindow)
{
    emit downloadThreadExist(downloadwindow);
}



void NewDownloadWindow::on_btnStart_clicked()
{
    QUrl url(ui->lineurl->text());

    downloadmessagewindow=new  DownloadMessageWindow;
    connect(downloadmessagewindow,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(ondownloadThreadExist(DownloadWindow*)));
    downloadmessagewindow->show();
}


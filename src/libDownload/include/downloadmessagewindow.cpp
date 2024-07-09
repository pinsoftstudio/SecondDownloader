#include "downloadmessagewindow.h"
#include "ui_downloadmessagewindow.h"

DownloadMessageWindow::DownloadMessageWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadMessageWindow)
{
    ui->setupUi(this);
}

DownloadMessageWindow::~DownloadMessageWindow()
{
    delete ui;
}

void DownloadMessageWindow::ondownloadThreadExist(DownloadWindow *downloadwindow)
{
    emit downloadThreadExist(downloadwindow);
}

void DownloadMessageWindow::on_btnStart_clicked()
{
    downloadwindow=new DownloadWindow;
    connect(downloadwindow,SIGNAL(downloadThreadExist(DownloadWindow*)),SLOT(ondownloadThreadExist(DownloadWindow*)));
    downloadwindow->show();

}

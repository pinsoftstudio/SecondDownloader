#include "downloadwindow.h"
#include "ui_downloadwindow.h"

DownloadWindow::DownloadWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadWindow)
{
    ui->setupUi(this);
    // downloader=new LibDownload
}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::ondownloadThreadExist(DownloadWindow *download)
{

}

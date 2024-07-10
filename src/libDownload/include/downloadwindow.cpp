#include "downloadwindow.h"
#include "ui_downloadwindow.h"
#include <curl.h>
DownloadWindow::DownloadWindow(QString url,QString saveFileName,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadWindow)
{
    URL=url;
    savedFilename=saveFileName;
    ui->setupUi(this);
    curl_global_init(CURL_GLOBAL_ALL);

    // downloader=new LibDownload
}

DownloadWindow::~DownloadWindow()
{
    delete ui;
}

void DownloadWindow::ondownloadThreadExist(DownloadWindow *download)
{

}

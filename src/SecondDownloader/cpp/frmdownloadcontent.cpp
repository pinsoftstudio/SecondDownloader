#include "header/frmdownloadcontent.h"
#include "ui_frmdownloadcontent.h"
#include <QSettings>
#include <QFile>
#include "mainwindow.h"
frmDownloadContent::frmDownloadContent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDownloadContent)
{
    ui->setupUi(this);
     MainWindow *Parent;
    Parent=qobject_cast<MainWindow *>(parent);
    connect(Parent,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(onExistSThread(DownloadWindow*)));
}

frmDownloadContent::~frmDownloadContent()
{
    delete ui;
}

void frmDownloadContent::setDark(bool isDark)
{
    QFile *qssFile=new QFile(this);
    if(isDark)
        qssFile->setFileName(":/mainform/qss/dark_frmmain.qss");
    else
        qssFile->setFileName(":/mainform/qss/white_frmmain.qss");
    qssFile->open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile->readAll());
    qssFile->close();
    setStyleSheet(styleSheet);
}

void frmDownloadContent::onExistSThread(DownloadWindow* downloadwindow)
{
    downloaders.append(downloadwindow);
    //下面的操作...
}

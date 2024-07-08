#include "header/frmdonate.h"
#include "ui_frmdonate.h"
#include <QSettings>
#include <QFile>
frmDonate::frmDonate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDonate)
{
    ui->setupUi(this);
}

frmDonate::~frmDonate()
{
    delete ui;
}

void frmDonate::setDark(bool isDark)
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

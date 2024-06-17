#include "header/frmsettings.h"
#include "ui_frmsettings.h"
#include <QSettings>
#include <QFile>
frmSettings::frmSettings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmSettings)
{
    ui->setupUi(this);
}

frmSettings::~frmSettings()
{
    delete ui;
}

void frmSettings::setDark(bool isDark)
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

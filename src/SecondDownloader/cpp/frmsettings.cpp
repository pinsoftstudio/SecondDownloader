#include "header/frmsettings.h"
#include "ui_frmsettings.h"
#include <QSettings>
#include <QFile>
#include <Style.h>
frmSettings::frmSettings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmSettings)
{
    ui->setupUi(this);
    if(isDark()){
        ;
    }else{
        ui->scrollDownload->setStyleSheet("background-color:white");
        ui->scollCommon->setStyleSheet("background-color:white");
    }

}

frmSettings::~frmSettings()
{
    delete ui;
}



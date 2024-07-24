#include "header/frmsettings.h"
#include "ui_frmsettings.h"
#include <QSettings>
#include <QFile>
#include <Style.h>
#include "QStandardPaths"
#include "QStringList"
#include "QDir"
#include "QFileInfo"
#include "QVariant"
#include "QDebug"
frmSettings::frmSettings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmSettings)
{
    ui->setupUi(this);
    //……
    if(isDark()){
        ;
    }else{
        ui->scrollDownload->setStyleSheet("background-color:white");
        ui->scollCommon->setStyleSheet("background-color:white");
    }
    iniSettings();

}

frmSettings::~frmSettings()
{
    delete ui;
}

void frmSettings::iniSettings()
{
    //自动运行
    QSettings set("Pinsoft","Seconddownloader");
    ui->chkRunAuto->setChecked(set.value("Common/Autorun",true).toBool());
    if(ui->chkRunAuto->isChecked()){
        ui->chkRunAuto->setCheckable(1);
    }else{
        ui->chkRunAuto->setCheckable(0);
    }
    ui->chkRunHide->setChecked("Common/HideAutorun");

    ui->rdbThemeFollow->setChecked(set.value("Style/FollowSystem",true).toBool());
    if(!ui->rdbThemeFollow->isChecked()){
        ui->rdbThemeBlack->setChecked(set.value("Style/isDark",false).toBool());
        ui->rdbThemeWhite->setChecked(!set.value("Style/isDark",false).toBool());
    }

    //语言
    ui->rdbLanDef->setChecked(set.value("Language/FollowSystem",true).toBool());
    if(!set.value("Language/FollowSystem",true).toBool()){

        QString Language=set.value("Language/Type","Chinese").toString();
        if(Language=="SimplifiedChinese"){
            ui->rdbLanZhSimplified->setChecked(1);
            ui->rdbLanZhTraditional->setChecked(0);
            ui->rdbLanEn->setChecked(0);
        }else if(Language=="TraditonalChinese"){
            ui->rdbLanZhSimplified->setChecked(0);
            ui->rdbLanZhTraditional->setChecked(1);
            ui->rdbLanEn->setChecked(0);
        }else if(Language=="English"){
            ui->rdbLanZhSimplified->setChecked(0);
            ui->rdbLanZhTraditional->setChecked(0);
            ui->rdbLanEn->setChecked(1);
        }else {
            set.setValue("Language/FollowSystem",true);
        }
    }

    //接管
    bool manageAll=set.value("Common/Manage/ManageAll",true).toBool();
    ui->rdbManageAll->setChecked(manageAll);
    ui->rdbManageNone->setChecked(!manageAll);

    //允许的协议
    ui->chkProtrolHttp->setChecked(set.value("Download/http",true).toBool());
    ui->chkProtrolHttps->setChecked(set.value("Download/https",true).toBool());
    ui->chkProtrolFtp->setChecked(set.value("Download/ftp",true).toBool());
    ui->chkProtrolFtps->setChecked(set.value("Download/ftps",true).toBool());
    ui->chkProtrolOthers->setChecked(set.value("Downloader/Others",true).toBool());

    //下载位置
    ui->lineSaveLocation->setText(set.value("Download/SavingLocation/location",
                                            QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)).toString());

    ui->chkDownLoadClip->setChecked(set.
                                    value("Download/AutoDownloadFromClipboard",false).toBool());

    //下载完成后
    ui->chkFinishedScan->setChecked(set.value("Download/ScanFile",true).toBool());
    ui->chkFinishedBell->setChecked(set.value("Download/FinishBell",false).toBool());
    QString mediaPath="C:/Windows/Media/";
    ui->comboFinishedBell->setEnabled(1);

    QStringList allWavFiles=getAllWavs(mediaPath);
    foreach (QString aWavFilePathName, allWavFiles) {
        QFileInfo aWavFileInfo(aWavFilePathName);
        ui->comboFinishedBell->addItem(aWavFileInfo.fileName(),QVariant(aWavFilePathName));

    }
     ui->comboFinishedBell->addItem(tr("自定义"),QVariant("自定义"));
    if(ui->chkFinishedBell->isChecked()){
         ui->comboFinishedBell->setEnabled(1);
    }else{
         ui->comboFinishedBell->setEnabled(0);
    }

    QString finishedToDo=set.value("Download/FinishedToDo","ShowDialog").toString();
    if(finishedToDo=="ShowDialog"){
        ui->rdbFinishedDisplay->setChecked(1);
        ui->rdbFinishedOpenFile->setChecked(0);
        ui->rdbFinishedOpenFolder->setChecked(0);
        ui->rdbFinishedNotNotice->setChecked(0);
    }else if(finishedToDo=="OpenFile"){
        ui->rdbFinishedDisplay->setChecked(0);
        ui->rdbFinishedOpenFile->setChecked(1);
        ui->rdbFinishedOpenFolder->setChecked(0);
        ui->rdbFinishedNotNotice->setChecked(0);
    }else if(finishedToDo=="OpenFolder"){
        ui->rdbFinishedDisplay->setChecked(0);
        ui->rdbFinishedOpenFile->setChecked(0);
        ui->rdbFinishedOpenFolder->setChecked(1);
        ui->rdbFinishedNotNotice->setChecked(0);
    }else if(finishedToDo=="NotNotice"){
        ui->rdbFinishedDisplay->setChecked(0);
        ui->rdbFinishedOpenFile->setChecked(0);
        ui->rdbFinishedOpenFolder->setChecked(0);
        ui->rdbFinishedNotNotice->setChecked(1);
    }else{
        ui->rdbFinishedDisplay->setChecked(1);
        ui->rdbFinishedOpenFile->setChecked(0);
        ui->rdbFinishedOpenFolder->setChecked(0);
        ui->rdbFinishedNotNotice->setChecked(0);
        set.setValue("Download/FinishedToDo","ShowDialog");
    }

    //github代理

    ui->chkGithubProxy->setChecked(set.value("Download/EnableGithubProxy",1).toBool());



}

QStringList frmSettings::getAllWavs(QString location)
{
    QStringList wavFiles;
    QDir dir(location);
    QFileInfoList entries=dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsLast);
    foreach (QFileInfo anEntry, entries) {

        qDebug()<<anEntry.absoluteFilePath();
        if(anEntry.isFile()){
            if(anEntry.suffix().toLower()=="wav"){

                wavFiles.append(anEntry.absoluteFilePath());
            }
        }else if(anEntry.isDir()){
            QStringList subWavFiles;
            subWavFiles=getAllWavs(anEntry.absoluteFilePath());
            wavFiles+=subWavFiles;
        }
    }
    return wavFiles;
}



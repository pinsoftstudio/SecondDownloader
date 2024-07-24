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
#include "QFileDialog"
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
    QSettings set("Pinsoft","SecondDownloader");
    ui->chkRunAuto->setChecked(set.value("Common/Autorun",1).toBool());
    if(ui->chkRunAuto->isChecked()){
        ui->chkRunAuto->setCheckable(1);
    }else{
        ui->chkRunAuto->setCheckable(0);
    }
    ui->chkRunHide->setChecked("Common/HideAutorun");

    //主题
    ui->rdbThemeFollow->setChecked(set.value("Style/FollowSystem",1).toBool());
    if(!ui->rdbThemeFollow->isChecked()){
        ui->rdbThemeBlack->setChecked(set.value("Style/isDark",0).toBool());
        ui->rdbThemeWhite->setChecked(!set.value("Style/isDark",0).toBool());
    }

    //语言
    ui->rdbLanDef->setChecked(set.value("Language/FollowSystem",1).toBool());
    if(!set.value("Language/FollowSystem",1).toBool()){

        QString Language=set.value("Language/Type","SimplifiedChinese").toString();
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
            set.setValue("Language/FollowSystem",1);
        }
    }

    //接管
    bool manageAll=set.value("Common/Manage/ManageAll",1).toBool();
    ui->rdbManageAll->setChecked(manageAll);
    ui->rdbManageNone->setChecked(!manageAll);

    //允许的协议
    ui->chkProtrolHttp->setChecked(set.value("Download/http",1).toBool());
    ui->chkProtrolHttps->setChecked(set.value("Download/https",1).toBool());
    ui->chkProtrolFtp->setChecked(set.value("Download/ftp",1).toBool());
    ui->chkProtrolFtps->setChecked(set.value("Download/ftps",1).toBool());
    ui->chkProtrolOthers->setChecked(set.value("Download/others",1).toBool());

    //下载位置
    ui->lineSaveLocation->setText(QDir::toNativeSeparators(set.value("Download/SavingLocation/location",
                                                                       QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)).toString()));

    ui->chkDownLoadClip->setChecked(set.
                                    value("Download/AutoDownloadFromClipboard",0).toBool());

    //下载完成后
    ui->chkFinishedScan->setChecked(set.value("Download/ScanFile",1).toBool());
    ui->chkFinishedBell->setChecked(set.value("Download/FinishBell",0).toBool());
    QString mediaPath="C:/Windows/Media/";
    ui->comboFinishedBell->setEnabled(1);

    QStringList allWavFiles=getAllWavs(mediaPath);

    ui->comboFinishedBell->addItem("bell.wav",QVariant("default"));
    foreach (QString aWavFilePathName, allWavFiles) {
        QFileInfo aWavFileInfo(aWavFilePathName);
        ui->comboFinishedBell->addItem(aWavFileInfo.fileName(),QVariant(aWavFilePathName));

    }

    ui->comboFinishedBell->addItem(tr("自定义"),QVariant(""));
    if(ui->chkFinishedBell->isChecked()){
        ui->comboFinishedBell->setEnabled(1);
        QString selectedFilePath=set.value("Download/BellPath","").toString();
        if(!selectedFilePath.isEmpty()){
            for(int i=0;i<ui->comboFinishedBell->count();i++){
                if(ui->comboFinishedBell->currentData(i).toString()==selectedFilePath){
                    ui->comboFinishedBell->setCurrentIndex(i);
                    break;
                }else{
                    if(i==ui->comboFinishedBell->count()-1){
                        ui->comboFinishedBell->setCurrentText(tr("自定义"));
                        ui->comboFinishedBell->setItemData(ui->comboFinishedBell->currentIndex(),selectedFilePath);
                        //这里会有翻译问题
                    }

                }
            }
        }else{
            ui->comboFinishedBell->setCurrentText("bell.wav");
        }
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

    connect(ui->comboFinishedBell,&QComboBox::currentTextChanged,this,&frmSettings::oncomboFinishedBellcurrentTextChanged);



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



void frmSettings::on_chkRunHide_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Common/HideAutorun",checked);

}


void frmSettings::on_chkRunAuto_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Common/Autorun",checked);
}


void frmSettings::on_rdbThemeFollow_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Style/FollowSystem",checked);
}


void frmSettings::on_rdbThemeWhite_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Style/FollowSystem",0);
    set.setValue("Style/isDark",!checked);
}


void frmSettings::on_rdbThemeBlack_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Style/FollowSystem",0);
    set.setValue("Style/isDark",checked);
}


void frmSettings::on_rdbLanDef_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/FollowSystem",1);
}


void frmSettings::on_rdbLanZhSimplified_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/Type","SimplifiedChinese");
    set.setValue("Language/FollowSystem",0);
}


void frmSettings::on_rdbLanZhTraditional_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/Type","TraditionalChinese");
    set.setValue("Language/FollowSystem",0);
}


void frmSettings::on_rdbLanEn_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/Type","English");
    set.setValue("Language/FollowSystem",0);
}


void frmSettings::on_rdbManageAll_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Common/Manage/ManageAll",1);

}


void frmSettings::on_rdbManageNone_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Common/Manage/ManageAll",0);
}


void frmSettings::on_chkProtrolHttps_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/https",checked);
}


void frmSettings::on_chkProtrolHttp_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/http",checked);
}


void frmSettings::on_chkProtrolFtp_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/ftp",checked);
}


void frmSettings::on_chkProtrolFtps_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/ftps",checked);
}


void frmSettings::on_chkProtrolOthers_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/others",checked);
}


void frmSettings::on_lineSaveLocation_textChanged(const QString &arg1)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/SavingLocation/location",arg1);
}


void frmSettings::on_chkDownLoadClip_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/AutoDownloadFromClipboard",checked);
}


void frmSettings::on_chkFinishedScan_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/ScanFile",checked);
}


void frmSettings::on_chkFinishedBell_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/FinishBell",checked);
        ui->comboFinishedBell->setEnabled(checked);
}


void frmSettings::oncomboFinishedBellcurrentTextChanged(const QString &arg1)
{

    QSettings set("Pinsoft","SecondDownloader");
    QString wavPath;
    if(arg1==QString(tr("自定义"))){
        wavPath=QFileDialog::getOpenFileName(this,"选择一个wav文件",
            set.value("Download/BellPath",QDir::currentPath()).toString(),tr("Wav文件(*.wav)"));
        if(!wavPath.isEmpty()){
            QFileInfo fi(wavPath);
            ui->comboFinishedBell->setItemData(ui->comboFinishedBell->currentIndex()
                                               ,QVariant(fi.absoluteFilePath()));
            set.setValue("Download/BellPath",QVariant(wavPath));
        }else{
            ui->comboFinishedBell->setCurrentText("bell.wav");
        }

    }

}


void frmSettings::on_rdbFinishedDisplay_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    if(checked){
        set.setValue("Download/FinishedToDo","ShowDialog");
    }
}


void frmSettings::on_rdbFinishedOpenFile_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    if(checked){
        set.setValue("Download/FinishedToDo","OpenFile");
    }
}


void frmSettings::on_rdbFinishedOpenFolder_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    if(checked){
        set.setValue("Download/FinishedToDo","OpenFolder");
    }
}


void frmSettings::on_rdbFinishedNotNotice_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    if(checked){
        set.setValue("Download/FinishedToDo","NotNotice");
    }
}


void frmSettings::on_chkGithubProxy_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Download/EnableGithubProxy",checked);
}


void frmSettings::on_btnSaveSelect_clicked()
{
    QString savePath="";
    savePath=QFileDialog::getExistingDirectory(this,"选择保存目录");
    if(savePath!=""){
        ui->lineSaveLocation->setText(QDir::toNativeSeparators(savePath));
    }
}


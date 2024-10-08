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
#include "QSoundEffect"
#include "dialogcrtinf.h"
#include "QTranslator"
frmSettings::frmSettings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmSettings)
{
    ui->setupUi(this);
    //……
    if(isDark()){
        ;
        ui->comboFinishedBell->setProperty("style","dark");
        ui->chhkUpdate->setProperty("style","dark");
        ui->chkDownLoadClip->setProperty("style","dark");
        ui->chkFinishedScan->setProperty("style","dark");
        ui->chkGithubProxy->setProperty("style","dark");
        ui->chkProtrolFtp->setProperty("style","dark");
        ui->chkProtrolFtps->setProperty("style","dark");
        ui->chkProtrolHttp->setProperty("style","dark");
        ui->chkProtrolHttps->setProperty("style","dark");
        ui->chkProtrolOthers->setProperty("style","dark");
        ui->chkRunAuto->setProperty("style","dark");
        ui->chkRunHide->setProperty("style","dark");
        ui->chkFinishedBell->setProperty("style","dark");
        ui->lineSaveLocation->setProperty("style","dark");
        setStyleSheet("QTabBar::tab{background-color: rgb(35,35,35);}");
        ui->scrollDownload->setStyleSheet("background-color:rgb(30,30,30)");
        ui->scollCommon->setStyleSheet("background-color:rgb(30,30,30)");
        ui->comboFinishedBell->setStyleSheet("QComboBox QAbstractItemView::item{border-radius: 6px; height: 30px;  color:white;background-color: rgb(44,44,44);}");
    }else{
        ui->comboFinishedBell->setProperty("style","light");
        ui->chhkUpdate->setProperty("style","light");
        ui->chkDownLoadClip->setProperty("style","light");
        ui->chkFinishedScan->setProperty("style","light");
        ui->chkGithubProxy->setProperty("style","light");
        ui->chkProtrolFtp->setProperty("style","light");
        ui->chkProtrolFtps->setProperty("style","light");

        ui->chkProtrolHttp->setProperty("style","light");
        ui->chkProtrolHttps->setProperty("style","light");
        ui->chkProtrolOthers->setProperty("style","light");
        ui->chkRunAuto->setProperty("style","light");
        ui->chkRunHide->setProperty("style","light");
        ui->chkFinishedBell->setProperty("style","light");
        ui->lineSaveLocation->setProperty("style","light");
        ui->scrollDownload->setStyleSheet("background-color:white");
        ui->scollCommon->setStyleSheet("background-color:white");
        ui->comboFinishedBell->setStyleSheet("QComboBox QAbstractItemView::item{border-radius: 6px; height: 30px;  color:white;background-color: rgb(240,240,240);}");
        setStyleSheet("QTabBar::tab{background-color: white;}");
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
        ui->chkRunHide->setCheckable(1);
    }else{
        ui->chkRunHide->setCheckable(0);
    }
    ui->chkRunHide->setChecked(set.value("Common/HideAutorun",1).toBool());

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
        }else if(Language=="TraditionalChinese"){
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
    bool manageAll=(!set.value("stopped",0).toBool());
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
    QSettings autoset("Microsoft","Windows");
    if(checked){

        QString runnerPath=QApplication::applicationDirPath()+"/run.exe";
        autoset.setValue("CurrentVersion/Run/SecondDownloader",QDir::toNativeSeparators(runnerPath));

    }else{
        autoset.setValue("CurrentVersion/Run/SecondDownloader","");

    }
}


void frmSettings::on_rdbThemeFollow_clicked(bool checked)
{
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新主题将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Style/FollowSystem",checked);


}


void frmSettings::on_rdbThemeWhite_clicked(bool checked)
{
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新主题将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Style/FollowSystem",0);
    set.setValue("Style/isDark",!checked);


}


void frmSettings::on_rdbThemeBlack_clicked(bool checked)
{
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新主题将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Style/FollowSystem",0);
    set.setValue("Style/isDark",checked);


}


void frmSettings::on_rdbLanDef_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/FollowSystem",1);
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新语言将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();



}


void frmSettings::on_rdbLanZhSimplified_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/Type","SimplifiedChinese");
    set.setValue("Language/FollowSystem",0);
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新语言将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();
}


void frmSettings::on_rdbLanZhTraditional_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/Type","TraditionalChinese");
    set.setValue("Language/FollowSystem",0);
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新语言将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();
}


void frmSettings::on_rdbLanEn_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("Language/Type","English");
    set.setValue("Language/FollowSystem",0);
    DialogCrtInf dia;
    QString title=tr("提示");
    QString content=tr("新语言将在重启后生效！");
    dia.setTitle(title);
    dia.setText(content);
    dia.exec();
}


void frmSettings::on_rdbManageAll_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("stopped",0);

}


void frmSettings::on_rdbManageNone_clicked(bool checked)
{
    QSettings set("Pinsoft","SecondDownloader");
    set.setValue("stopped",1);
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
            set.setValue("Download/BellPath",wavPath);
        }else{
            ui->comboFinishedBell->setCurrentText("bell.wav");
        }

    }else{
        QVariant wavPath=ui->comboFinishedBell->currentData();
        set.setValue("Download/BellPath",wavPath);

    }

    QString finalWavPath=ui->comboFinishedBell->itemData(ui->comboFinishedBell->currentIndex()).toString();
    if(finalWavPath=="default"){
        finalWavPath=":/common/res/notice.wav";
    }
    QSoundEffect *sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(finalWavPath));
    sound->setVolume(1.0);
    sound->play();


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





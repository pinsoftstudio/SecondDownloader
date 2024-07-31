#include <QSettings>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include "header/Style.h"
#include <QMessageBox>
#include <downloadwindow.h>
#include <QUrl>
#include <QDebug>
#include <QtCore/QSharedMemory>
#include <QSystemTrayIcon>
#include <QList>
#include <newdownloadwindow.h>
#include <QDesktopServices>
#include <QObject>
#include <QAction>
#include <QBuffer>
#include <QDir>
#include <QLocale>
// #include "header/dialogquestion.h"
#include "header/mainwindow.h"
static DownloadMessageWindow *dw=Q_NULLPTR;
static MainWindow *w=Q_NULLPTR;
static QTimer detectWindowShow;
static QSharedMemory shared;
QTranslator *tran=NULL;
QTranslator *tran1=NULL;
QTranslator *tran2=NULL;
void detectShowReq(){


}
void createMainTray(){


    QSystemTrayIcon *mainTray=new QSystemTrayIcon;
    mainTray->setIcon(QIcon(":/frmmain/res/icon.ico"));
    QMenu *menu=new QMenu;
    QAction *actOpen=new QAction(menu);
    QAction *actNew=new QAction(menu);
    QAction *actSettings=new QAction(menu);
    QAction *actDownloadContent=new QAction(menu);
    QAction *actDonate=new QAction(menu);
    QAction *actAbout=new QAction(menu);
    QAction *actGithub=new QAction(menu);
    QAction *actCheckForUpdate=new QAction(menu);
    QAction *actExit=new QAction(menu);
    actOpen->setText(QObject::tr("打开主界面(&O)"));
    actNew->setText(QObject::tr("新建下载任务(&N)"));
    actDownloadContent->setText(QObject::tr("管理下载任务(&M)"));
    actSettings->setText(QObject::tr("打开设置(&S)"));
    actDonate->setText(QObject::tr("捐赠(&D)"));
    actAbout->setText(QObject::tr("关于SecondDownloader(&A)"));
    actGithub->setText(QObject::tr("在Github上的仓库(&R)"));
    actCheckForUpdate->setText(QObject::tr("检查更新(&U)"));
    actExit->setText(QObject::tr("退出本软件(&E)"));

    if(isDark()){
        actOpen->setIcon(QIcon(":/menu/res/menuico/main_white.png"));
        actNew->setIcon(QIcon(":/menu/res/menuico/new_white.png"));
        actDownloadContent->setIcon(QIcon(":/menu/res/menuico/manage_white.png"));
        actSettings->setIcon(QIcon(":/menu/res/menuico/settings_white.png"));
        actDonate->setIcon(QIcon(":/menu/res/menuico/donate_white.png"));
        actAbout->setIcon(QIcon(":/menu/res/menuico/about_white.png"));
        actGithub->setIcon(QIcon(":/menu/res/menuico/github-fill_white.png"));
        actCheckForUpdate->setIcon(QIcon(":/menu/res/menuico/update_white.png"));
        actExit->setIcon(QIcon(":/menu/res/menuico/exit_white.png"));
    }else{
        actOpen->setIcon(QIcon(":/menu/res/menuico/main_dark.png"));
        actNew->setIcon(QIcon(":/menu/res/menuico/new_dark.png"));
        actDownloadContent->setIcon(QIcon(":/menu/res/menuico/manage_dark.png"));
        actSettings->setIcon(QIcon(":/menu/res/menuico/settings_dark.png"));
        actDonate->setIcon(QIcon(":/menu/res/menuico/donate_dark.png"));
        actAbout->setIcon(QIcon(":/menu/res/menuico/about_dark.png"));
        actGithub->setIcon(QIcon(":/menu/res/menuico/github-fill_dark.png"));
        actCheckForUpdate->setIcon(QIcon(":/menu/res/menuico/update_dark.png"));
        actExit->setIcon(QIcon(":/menu/res/menuico/exit_dark.png"));
    }


    menu->addAction(actOpen);
    menu->addAction(actNew);
    menu->addAction(actDownloadContent);
    menu->addAction(actSettings);
    menu->addAction(actDonate);
    menu->addSeparator();
    menu->addAction(actAbout);
    menu->addAction(actGithub);
    menu->addAction(actCheckForUpdate);
    menu->addSeparator();
    menu->addAction(actExit);
    QObject::connect(actOpen,&QAction::triggered,[](){
        w->showWithMode(0);
    });
    QObject::connect(actNew,&QAction::triggered,[](){
        NewDownloadWindow *w=new NewDownloadWindow;
        w->show();
    });
    QObject::connect(actDownloadContent,&QAction::triggered,[](){
        w->showWithMode(1);
    });
    QObject::connect(actSettings,&QAction::triggered,[](){
         w->showWithMode(2);
    });
    QObject::connect(actDonate,&QAction::triggered,[](){
         w->showWithMode(3);
    });
    QObject::connect(actAbout,&QAction::triggered,[](){
        //about
    });
    QObject::connect(actGithub,&QAction::triggered,[](){
        QDesktopServices::openUrl(QUrl("https://github.com/pinsoftstudio/SecondDownloader"));
    });
    QObject::connect(actCheckForUpdate,&QAction::triggered,[](){
        //update
    });
    QObject::connect(actExit,&QAction::triggered,[](){
        QApplication *app;
        app->exit(0);
    });
    QObject::connect(mainTray,&QSystemTrayIcon::activated,[](QSystemTrayIcon::ActivationReason reason){
        if(reason!=QSystemTrayIcon::Context){
             w->show();
        }

    });
    mainTray->setContextMenu(menu);
    mainTray->show();
}

bool isSingleInstance(const char* shared_memory_name)
{
    bool result;
    shared.setKey(shared_memory_name);
    if (shared.attach())
    {
        result=false;
    }
    else
    {
        result=true;
        shared.create(1);
    }
    return result;
}
void installTranslator(QApplication &a)
{
    tran=new QTranslator;
    tran1=new QTranslator;
    tran2=new QTranslator;
    QSettings set("Pinsoft","SecondDownloader");
    QString Language;
    if(!set.value("Language/FollowSystem",1).toBool()){
        Language=set.value("Language/Type","SimplifiedChinese").toString();
        if(Language=="SimplifiedChinese"){
            tran->load("translations/SecondDownload_zh_CN.qm");
            tran1->load("translations/LibDownload_zh_CN.qm");
            tran2->load("translations/LibDialog_zh_CN.qm");

        }else if(Language=="TraditionalChinese"){
            tran->load("translations/SecondDownload_zh_TW.qm");
            tran1->load("translations/LibDownload_zh_TW.qm");
            tran2->load("translations/LibDialog_zh_TW.qm");

        }else if(Language=="English"){
            tran->load("translations/SecondDownload_en_US.qm");
            tran1->load("translations/LibDownload_en_US.qm");
            tran2->load("translations/LibDialog_en_US.qm");

        }else {

        }
    }else{
        QLocale lc;
        switch (lc.language()){
        case QLocale::Chinese:{
            tran->load("translations/SecondDownload_zh_CN.qm");
            tran1->load("translations/LibDownload_zh_CN.qm");
            tran2->load("translations/LibDialog_zh_CN.qm");
            break;
        }
        case QLocale::English:{
            tran->load("translations/SecondDownload_en_US.qm");
            tran1->load("translations/LibDownload_en_US.qm");
            tran2->load("translations/LibDialog_en_US.qm");
            break;
        }
        default:{
            tran->load("translations/SecondDownloader_en_US.qm");
            tran1->load("translations/LibDownload_en_US.qm");
            tran2->load("translations/LibDialog_en_US.qm");
            break;
        }

        }
    }
    a.installTranslator(tran);
    a.installTranslator(tran1);
    a.installTranslator(tran2);


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool MainAppIsRunning=0;
    bool needExit=1;
    if(!isSingleInstance("SecondDownloader"))
    {
        MainAppIsRunning=1;
    }
    a.setQuitOnLastWindowClosed(0);
    installTranslator(a);
    QSettings set("Pinsoft","SecondDownloader");
    bool autorun=set.value("Common/Autorun",1).toBool();
    bool silent=set.value("Common/HideAutorun",1).toBool();
    if(autorun){
        QSettings autoset("Microsoft","Windows");
        QString runnerPath=QApplication::applicationDirPath()+"/run.exe";
        autoset.setValue("CurrentVersion/Run/SecondDownloader",QDir::toNativeSeparators(runnerPath));

    }
    QStringList arguments=a.arguments();
    if(arguments.size()>1){
        QString url=arguments.at(1);

        if(url=="autorun"){
            setCommonStyle();
            createMainTray();
            w=new MainWindow(0);

            QObject::connect(&detectWindowShow,&QTimer::timeout,w,[]{
                link:
                    if(!shared.lock()){
                        goto link;
                    }

                    bool needToOpen=0;
                    QBuffer buffer;
                    buffer.setData((char*)shared.constData(),shared.size());
                    buffer.open(QBuffer::ReadWrite);
                    QDataStream stream(&buffer);
                    stream>>needToOpen;

                    shared.unlock();
                    if(needToOpen){
                        if(w!=Q_NULLPTR){
                            w->show();
                        }
                    lnk:
                        if(!shared.lock()){
                            goto lnk;
                        }
                        needToOpen=0;
                        char *toKey=static_cast<char*>(shared.data());
                        QBuffer keyBuffer;
                        keyBuffer.open(QBuffer::WriteOnly);
                        QDataStream keyStream(&keyBuffer);
                        keyStream<<needToOpen;

                        memcpy(toKey,keyBuffer.data(),keyBuffer.size());
                        shared.unlock();
                    }
            });
            detectWindowShow.start(100);
            if(silent){
                w->hide();
            }else{
                w->show();
            }

        }else{

            static QSharedMemory urlShare("newUrl");
            if(!urlShare.create(1024)){
                if(urlShare.attach()){
                    if(urlShare.lock()){

                        char* to=static_cast<char*>(urlShare.data());
                        QBuffer buffer;
                        buffer.open(QBuffer::ReadWrite);
                        QDataStream stream(&buffer);
                        stream<<url;
                        memcpy(to,buffer.data().data(),buffer.size());
                        urlShare.unlock();
                        // urlShare.detach();
                    }
                }
                return 0;
            }else{
                setCommonStyle();
                createMainTray();
                w=new MainWindow(0);
                w->hide();
                if(urlShare.lock()){
                    char* to=static_cast<char*>(urlShare.data());
                    QBuffer buffer;
                    buffer.open(QBuffer::ReadWrite);
                    QDataStream stream(&buffer);
                    stream<<url;
                    memcpy(to,buffer.data().data(),buffer.size());
                    urlShare.unlock();
                }
            }
        }

    }else{
        if(!MainAppIsRunning){
            setCommonStyle();
            createMainTray();
            w=new MainWindow(0);

            QObject::connect(&detectWindowShow,&QTimer::timeout,w,[]{
                link:
                    if(!shared.lock()){
                        goto link;
                    }

                    bool needToOpen=0;
                    QBuffer buffer;
                    buffer.setData((char*)shared.constData(),shared.size());
                    buffer.open(QBuffer::ReadWrite);
                    QDataStream stream(&buffer);
                    stream>>needToOpen;

                    shared.unlock();
                    if(needToOpen){
                        if(w!=Q_NULLPTR){
                            w->show();
                        }
                    lnk:
                        if(!shared.lock()){
                            goto lnk;
                        }
                        needToOpen=0;
                        char *toKey=static_cast<char*>(shared.data());
                        QBuffer keyBuffer;
                        keyBuffer.open(QBuffer::WriteOnly);
                        QDataStream keyStream(&keyBuffer);
                        keyStream<<needToOpen;

                        memcpy(toKey,keyBuffer.data(),keyBuffer.size());
                        shared.unlock();
                    }
            });
            detectWindowShow.start(100);
            w->show();
        }else{
            if(shared.lock()){
                bool open=1;
                char* to=static_cast<char*>(shared.data());
                QBuffer buffer;
                buffer.open(QBuffer::ReadWrite);
                QDataStream stream(&buffer);
                stream<<open;
                memcpy(to,buffer.data().data(),buffer.size());
                shared.unlock();
            }
            return 0;
        }

    }
    return a.exec();
}

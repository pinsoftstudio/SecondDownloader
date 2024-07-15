#include <QSettings>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include "header/mainwindow.h"
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
// #include "header/dialogquestion.h"
static MainWindow *w=Q_NULLPTR;
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


    actOpen->setIcon(QIcon(":/menu/res/menuico/main.png"));
    actNew->setIcon(QIcon(":/menu/res/menuico/new.png"));
    actDownloadContent->setIcon(QIcon(":/menu/res/menuico/manage.png"));
    actSettings->setIcon(QIcon(":/menu/res/menuico/settings.png"));
    actDonate->setIcon(QIcon(":/menu/res/menuico/donate.png"));
    actAbout->setIcon(QIcon(":/menu/res/menuico/about.png"));
    actGithub->setIcon(QIcon(":/menu/res/menuico/github-fill.png"));
    actCheckForUpdate->setIcon(QIcon(":/menu/res/menuico/update.png"));
    actExit->setIcon(QIcon(":/menu/res/menuico/exit.png"));

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
    mainTray->setContextMenu(menu);
    mainTray->show();





}
bool isSingleInstance(const char* shared_memory_name)
{
    bool result;
    static QSharedMemory shared(shared_memory_name);
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
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SecondDownloader_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    setCommonStyle();
    QStringList ag=a.arguments();
    // ag.append("sdp://https://down-tencent.huorong.cn/sysdiag-all-x64-6.0.1.0-2024.07.04.1.exe");

    if(ag.size()>1){
        if(!QUrl(ag.at(1)).scheme().isEmpty() &&ag.at(1).count()>=6){
            QMessageBox::information(nullptr,"",ag.at(1));
                if(ag.at(1).left(6).toLower()=="sdp://"){
                        QString  url=ag.at(1).right(ag.at(1).count()-6);
                        DownloadMessageWindow *dw=new   DownloadMessageWindow(url,nullptr,1);
                        dw->show();
                        bool needExit=0;
                }

        }

    }else{
        if(!MainAppIsRunning){

            w=new MainWindow(0);
            w->show();
            createMainTray();
        }else{
            QApplication *app1;
            return 0;
        }

    }

    if(MainAppIsRunning && needExit){
        QApplication *app1;
         return 0;
    }


    return a.exec();
}

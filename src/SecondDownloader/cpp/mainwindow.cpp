#include "ui_mainwindow.h"
#include <header/Style.h>
#include <header/mainwindow.h>
#include <header/frmmainpage.h>
#include <header/frmdownloadcontent.h>
#include <header/frmsettings.h>
#include <header/frmdonate.h>
#include "QCloseEvent"
#include "QSettings"
#include "QDebug"
#include "QTimer"
#include "QClipboard"
#include "QRegularExpression"
#include "downloadmessagewindow.h"
#include "QSettings"
MainWindow::MainWindow(int mode, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    addWidgetTostackedWidget();
    switch (mode) {
    case 0:
        ui->stackedWidget->setCurrentIndex(0);
        on_toolMain_clicked();
        break;
    case 1:
        ui->stackedWidget->setCurrentIndex(1);
        on_toolDownload_clicked();
        break;
    case 2:
        ui->stackedWidget->setCurrentIndex(2);
         on_toolSettings_clicked();
        break;
    case 3:
        ui->stackedWidget->setCurrentIndex(3);
        on_toolDonate_clicked();
        break;

    default:
        break;


    }
    addToLastUrlList();
    tmNeedLaunchGetUrl=new QTimer;
    tmGetClipUrl=new QTimer;
    connect(tmGetClipUrl,&QTimer::timeout,this,&MainWindow::onGetClipUrl);
    connect(tmNeedLaunchGetUrl,&QTimer::timeout,this,[&]{
        QSettings set("Pinsoft","SecondDownloader");
        if(set.value("Download/AutoDownloadFromClipboard",0).toBool()){
            if(!tmGetClipUrl->isActive()){
                tmGetClipUrl->start(1000);
            }

        }else{
            if(tmGetClipUrl->isActive()){
                tmGetClipUrl->stop();
            }

        }
    });
    tmNeedLaunchGetUrl->start(1000);




    // ui->toolDownload->setProperty("select","false");
    // ui->toolDonate->setProperty("select","false");
    // ui->toolSettings->setProperty("select","false");
    setClassToolButtonStyle();

    //BUG:Qt 6.7 QToolButton无法connectSlotByName()
    connect(ui->toolMenu,&QToolButton::clicked,this,&MainWindow::on_toolMenu_clicked);
    connect(ui->toolMain,&QToolButton::clicked,this,&MainWindow::on_toolMain_clicked);
    connect(ui->toolDownload,&QToolButton::clicked,this,&MainWindow::on_toolDownload_clicked);
    connect(ui->toolDonate,&QToolButton::clicked,this,&MainWindow::on_toolDonate_clicked);
    connect(ui->toolSettings,&QToolButton::clicked,this,&MainWindow::on_toolSettings_clicked);



}

void MainWindow::addWidgetTostackedWidget()
{

    dwncontent=new frmDownloadContent(this);
    mainPage=new frmMainPage(this);
    connect(mainPage,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(ondownloadThreadExist(DownloadWindow*)));
    set=new frmSettings(this);
    donate=new frmDonate(this);

    ui->stackedWidget->insertWidget(0,mainPage);
    connect(mainPage,&frmMainPage::requestPage,this,&MainWindow::onRequestPageChange);

    ui->stackedWidget->insertWidget(1,dwncontent);

    ui->stackedWidget->insertWidget(2,donate);
    ui->stackedWidget->insertWidget(3,set);



}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showWithMode(int mode)
{

    switch (mode) {
    case 0:
        ui->stackedWidget->setCurrentIndex(0);
        on_toolMain_clicked();
        break;
    case 1:
        ui->stackedWidget->setCurrentIndex(1);
        on_toolDownload_clicked();
        break;
    case 2:
        ui->stackedWidget->setCurrentIndex(2);
        on_toolSettings_clicked();
        break;
    case 3:
        ui->stackedWidget->setCurrentIndex(3);
        on_toolDonate_clicked();
        break;

    default:
        break;


    }
    show();
}

void MainWindow::addToLastUrlList()
{
    QSettings set("Pinsoft","SecondDownloader");
    QString urls=set.value("Common/LastUrlString","").toString();
    QRegularExpression exp("(.*?)\n");
    QRegularExpressionMatchIterator expInt=exp.globalMatch(urls);
    while(expInt.hasNext()){
        QRegularExpressionMatch match=expInt.next();
        QString preUrlstr=match.captured(0);
        LastUrlList.append(preUrlstr);
    }

}

void MainWindow::setClassToolButtonStyle()
{

    if(isDark()){
        ui->toolMain->setIcon(QIcon(":/MainWindow/res/Main-Page_dark.png"));
        ui->toolDownload->setIcon(QIcon(":/MainWindow/res/Download-Content_dark.png"));
        ui->toolDonate->setIcon(QIcon(":/MainWindow/res/Donate_dark.png"));
        ui->toolSettings->setIcon(QIcon(":/MainWindow/res/Settings_dark.png"));
         ui->toolMenu->setIcon(QIcon(":/MainWindow/res/Menu_dark.png"));
    }else{
        ui->toolMain->setIcon(QIcon(":/MainWindow/res/Main-Page_white.png"));
        ui->toolDownload->setIcon(QIcon(":/MainWindow/res/Download-Content_white.png"));
        ui->toolDonate->setIcon(QIcon(":/MainWindow/res/Donate_white.png"));
        ui->toolSettings->setIcon(QIcon(":/MainWindow/res/Settings_white.png"));

        ui->toolMenu->setIcon(QIcon(":/MainWindow/res/Menu_white.png"));
    }

    QSettings settings("Pinsoft","SecondDownloader");
    bool maxed=settings.value("MainWindow/ToolbarMaxed",0).toBool();
    if(maxed){
        ui->toolMain->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolDownload->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolDonate->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolSettings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolMain->setMinimumWidth(201);
        ui->toolMain->setFixedWidth(201);

        ui->toolDownload->setMinimumWidth(201);
        ui->toolDownload->setFixedWidth(201);

        ui->toolDonate->setMinimumWidth(201);
        ui->toolDonate->setFixedWidth(201);

        ui->toolSettings->setMinimumWidth(201);
        ui->toolSettings->setFixedWidth(201);

    }else{
        ui->toolMain->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolDownload->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolDonate->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolSettings->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolMain->setMinimumWidth(35);
        ui->toolMain->setFixedWidth(35);

        ui->toolDownload->setMinimumWidth(35);
        ui->toolDownload->setFixedWidth(35);

        ui->toolDonate->setMinimumWidth(35);
        ui->toolDonate->setFixedWidth(35);

        ui->toolSettings->setMinimumWidth(35);
        ui->toolSettings->setFixedWidth(35);

    }
    ui->toolMenu->setChecked(!maxed);
}


void MainWindow::on_toolMenu_clicked()
{

    bool checked=ui->toolMenu->isChecked();
    QSettings settings("Pinsoft","SecondDownloader");
    if(checked){
        settings.setValue("MainWindow/ToolbarMaxed",0);
    }else{
        settings.setValue("MainWindow/ToolbarMaxed",1);
    }
    if(checked){
        ui->toolMain->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolDownload->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolDonate->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolSettings->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ui->toolMain->setMinimumWidth(35);
        ui->toolMain->setFixedWidth(35);

        ui->toolDownload->setMinimumWidth(35);
        ui->toolDownload->setFixedWidth(35);

        ui->toolDonate->setMinimumWidth(35);
        ui->toolDonate->setFixedWidth(35);

        ui->toolSettings->setMinimumWidth(35);
        ui->toolSettings->setFixedWidth(35);


    }else{
        ui->toolMain->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolDownload->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolDonate->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolSettings->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->toolMain->setMinimumWidth(201);
        ui->toolMain->setFixedWidth(201);

        ui->toolDownload->setMinimumWidth(201);
        ui->toolDownload->setFixedWidth(201);

        ui->toolDonate->setMinimumWidth(201);
        ui->toolDonate->setFixedWidth(201);

        ui->toolSettings->setMinimumWidth(201);
        ui->toolSettings->setFixedWidth(201);

    }

}




void MainWindow::on_toolMain_clicked()
{

    ui->toolMain->setProperty("select","true");

    ui->toolDownload->setProperty("select","false");
    ui->toolDonate->setProperty("select","false");
    ui->toolSettings->setProperty("select","false");
    ui->stackedWidget->setCurrentIndex(0);
    setCommonStyle();


}


void MainWindow::on_toolDownload_clicked()
{
    ui->toolMain->setProperty("select","false");

    ui->toolDownload->setProperty("select","true");
    ui->toolDonate->setProperty("select","false");
    ui->toolSettings->setProperty("select","false");
    ui->stackedWidget->setCurrentIndex(1);
    setCommonStyle();
}


void MainWindow::on_toolDonate_clicked()
{
    ui->toolMain->setProperty("select","false");

    ui->toolDownload->setProperty("select","false");
    ui->toolDonate->setProperty("select","true");
    ui->toolSettings->setProperty("select","false");
    ui->stackedWidget->setCurrentIndex(2);
    setCommonStyle();
}


void MainWindow::on_toolSettings_clicked()
{
    ui->toolMain->setProperty("select","false");

    ui->toolDownload->setProperty("select","false");
    ui->toolDonate->setProperty("select","false");
    ui->toolSettings->setProperty("select","true");
    ui->stackedWidget->setCurrentIndex(3);
    setCommonStyle();
}


void MainWindow::onRequestPageChange(int i,int mode=0)
{
    switch (i) {
    case 0:
        on_toolMain_clicked();
        break;
    case 1:
        on_toolDownload_clicked();
        frmDownloadContent::displayMode dis;
        if(mode==0){
            dis=frmDownloadContent::all;
        }else if(mode==1){
            dis=frmDownloadContent::downloading;
        }else if(mode==2){
            dis=frmDownloadContent::succeed;
        }else if(mode==3){
            dis=frmDownloadContent::faild;
        }
        dwncontent->setDisplayMode(dis);

        break;
    case 2:
        on_toolDonate_clicked();
        break;
    case 3:
        on_toolSettings_clicked();
        break;
    default:
        break;
    }
}

void MainWindow::onGetClipUrl()
{
    QSettings set("Pinsoft","SecondDownloader");
    QStringList noList;
    if(!set.value("Download/http",1).toBool()){
        noList.append("http");
    }
    if(!set.value("Download/https",1).toBool()){
        noList.append("https");
    }
    if(!set.value("Download/ftp",1).toBool()){
        noList.append("ftp");
    }
    if(!set.value("Download/ftps",1).toBool()){
        noList.append("ftps");
    }
    if(!set.value("Download/others",1).toBool()){
        noList.append("others");
    }
    QString clipString=QApplication::clipboard()->text()+"\n";
    QRegularExpression exp("(.*?)\n");
    QRegularExpressionMatchIterator expInt=exp.globalMatch(clipString);
    QStringList usableUrl;

    while(expInt.hasNext()){
        QString preurl;
        QRegularExpressionMatch match=expInt.next();
        QString preUrlstr=match.captured(0);
        QUrl preUrl(preUrlstr);
        QString preUrlStrScheme=preUrl.scheme().toLower();
        bool containsNoOthers=0;
        bool containedNoUrl=1;
        if(noList.count()==0){
            containedNoUrl=0;
            containsNoOthers=0;
        }
        foreach (QString aScheme, noList) {
            if(aScheme=="others"){
                containsNoOthers=1;
            }
            if(aScheme!=preUrlStrScheme){
                containedNoUrl=0;
            }else{
                containedNoUrl=1;
            }

        }
        if(((containsNoOthers) &&(!containedNoUrl) &&
             (preUrlStrScheme=="https" || preUrlStrScheme=="http" || preUrlStrScheme=="ftps" ||preUrlStrScheme=="ftp"))
            || ((!containsNoOthers) && (!containedNoUrl) &&(!preUrlStrScheme.isEmpty()))){
            usableUrl.append(preUrlstr);
        }


    }
    QStringList preLastUrl;
    bool detectedOne=0;
    int urlCount=LastUrlList.count();
    int i=0;
    foreach(QString aUrlStr,usableUrl){
        i=0;
        bool isTwice=0;
        foreach (QString aLastUrlStr, LastUrlList) {
            i++;
            if(aUrlStr==aLastUrlStr){
                isTwice=1;
                break;
            }
        }
        if(!isTwice && i==urlCount){
            DownloadMessageWindow *dw=new DownloadMessageWindow(aUrlStr.trimmed(),nullptr,1);
            dw->show();
            preLastUrl.append(aUrlStr);
            detectedOne=1;
        }
    }
    if(detectedOne){
        LastUrlList.clear();
        LastUrlList=preLastUrl;
        QSettings set("Pinsoft","SecondDownloader");
        QString finalUrlSet;
        foreach(QString aToReg,LastUrlList){
            finalUrlSet+=aToReg+"\n";
        }
        set.setValue("Common/LastUrlString",finalUrlSet);
    }




}




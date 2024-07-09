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
#include <header/frmdownloadcontent.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    addWidgetTostackedWidget();
    addToStyleControl(this);
    ui->toolMain->setProperty("select","true");

    // ui->toolDownload->setProperty("select","false");
    // ui->toolDonate->setProperty("select","false");
    // ui->toolSettings->setProperty("select","false");
    setThisStyle();
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
    frmDownloadContent *dwncontent;
    dwncontent=new frmDownloadContent(this);
    dwncontent->setDark(dark);
    mainPage=new frmMainPage(this);
    mainPage->setDark(dark);
    connect(mainPage,SIGNAL(downloadThreadExist(DownloadWindow*)),this,SLOT(ondownloadThreadExist(DownloadWindow*)));
    set=new frmSettings(this);
    set->setDark(dark);
    donate=new frmDonate(this);
    donate->setDark(dark);

    ui->stackedWidget->insertWidget(0,mainPage);
    ui->stackedWidget->insertWidget(1,dwncontent);
    ui->stackedWidget->insertWidget(2,set);
    ui->stackedWidget->insertWidget(3,donate);
    ui->stackedWidget->setCurrentIndex(0);

}
MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::ondownloadThreadexist(DownloadWindow *DownloadWindow)
// {

// }

// void MainWindow::closeEvent(QCloseEvent *event)
// {
//     event->accept();
// }


// void MainWindow::closeEvent(QCloseEvent *event)  override
// {
//     // 在这里处理关闭事件
//     // 例如，你可能想在这里弹出对话框询问用户是否真的想退出
//     // 如果不想关闭窗口，可以调用 event->ignore();

//     // 如果调用 event->accept();（或默认），窗口将关闭

// }



void MainWindow::setClassToolButtonStyle()
{

    if(dark){
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


// void MainWindow::on_toolMenu_clicked(bool checked)
// {

//     QSettings settings("Pinsoft","SecondDownloader");
//     if(checked){
//         settings.setValue("MainWindow/ToolbarMaxed",0);
//     }else{
//         settings.setValue("MainWindow/ToolbarMaxed",1);
//     }
//     if(checked){
//         ui->toolMain->setToolButtonStyle(Qt::ToolButtonIconOnly);
//         ui->toolDownload->setToolButtonStyle(Qt::ToolButtonIconOnly);
//         ui->toolDonate->setToolButtonStyle(Qt::ToolButtonIconOnly);
//         ui->toolSettings->setToolButtonStyle(Qt::ToolButtonIconOnly);

//     }
// }




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
    setThisStyle();


}


void MainWindow::on_toolDownload_clicked()
{
    ui->toolMain->setProperty("select","false");

    ui->toolDownload->setProperty("select","true");
    ui->toolDonate->setProperty("select","false");
    ui->toolSettings->setProperty("select","false");
    ui->stackedWidget->setCurrentIndex(1);
     setThisStyle();
}


void MainWindow::on_toolDonate_clicked()
{
    ui->toolMain->setProperty("select","false");

    ui->toolDownload->setProperty("select","false");
    ui->toolDonate->setProperty("select","true");
    ui->toolSettings->setProperty("select","false");
    ui->stackedWidget->setCurrentIndex(2);
     setThisStyle();
}


void MainWindow::on_toolSettings_clicked()
{
    ui->toolMain->setProperty("select","false");

    ui->toolDownload->setProperty("select","false");
    ui->toolDonate->setProperty("select","false");
    ui->toolSettings->setProperty("select","true");
    ui->stackedWidget->setCurrentIndex(3);
     setThisStyle();
}




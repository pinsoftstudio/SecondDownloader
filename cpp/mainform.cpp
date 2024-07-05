#include "header/mainform.h"
#include "ui_mainform.h"
// #include <header/windowsizeadapter.h>
#include <QMessageBox>
// #include <header/stackedwidgetadapter.h>
#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QIcon>
mainform::mainform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainform)
{
    ui->setupUi(this);
    // adaptWindowAndControls();
    configWindowStyle();
    addWidgetTostackedWidget();
    // adaptStackedWidgetAndSubControls();
    ui->btnMainPage->setStyleSheet("border-image: url(:/mainform/res/Main-Page_selected_gradient.png);");


}

mainform::~mainform()
{
    delete ui;
}

// void mainform::adaptWindowAndControls()
// {
//      WindowSizeAdapter   adapter;
//     adapter.setWindow(this);
//     adapter.addWidget(this->ui->stackedWidget);
//     adapter.addWidget(this->ui->btnClose);
//     adapter.addWidget(this->ui->btnMin);
//     adapter.addWidget(this->ui->btnSettings);
//     adapter.addWidget(this->ui->btnChangeStyle);
//     adapter.addWidget(this->ui->btnMainPage);
//     adapter.addWidget(this->ui->btnDownloadContent);
//     adapter.addWidget(this->ui->btnDonate);
//     adapter.addWidget(this->ui->btnMenu);
//     adapter.adaptAll();
//     siderBarRect=adapter.getPaintRect();
// }

void mainform::addWidgetTostackedWidget()
{   mainPage=new frmMainPage(this);
    mainPage->setDark(dark);
    dwncontent=new frmDownloadContent(this);
    dwncontent->setDark(dark);
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

// void mainform::adaptStackedWidgetAndSubControls()
// {
//     StackedWidgetAdapter *swadpt=new StackedWidgetAdapter(ui->stackedWidget);
//     swadpt->setStackedWidget(ui->stackedWidget);
//     swadpt->adapt();
// }

void mainform::configWindowStyle()
{
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::FramelessWindowHint);
    QSettings settings("Pinsoft","SecondDownloader");
    bool isDark=0;
    //QString rootReg="HKEY_LOCAL_MACHINE/SOFTWARE/Pinsoft/";
    // QMessageBox::information(this,QString::asprintf(rooReg.toLocal8Bit(),"%sSecondDownloader/Style/isDark"),QString::asprintf(rooReg.toLocal8Bit()));
    isDark=settings.value("Style/isDark",0).toBool();
    qDebug()<<isDark;
    QFile *qssFile=new QFile(this);
    if(isDark){
        qssFile->setFileName(":/mainform/qss/dark_mainform.qss");
        dark=isDark;
        ui->btnChangeStyle->setStyleSheet("border-image:url(:/mainform/res/ChangeStyle_dark.png)");
        ui->btnMenu->setStyleSheet("border-image:url(:/mainform/res/Menu_dark.png)");
        repaint();
    }else{
        qssFile->setFileName(":/mainform/qss/white_mainform.qss");
        dark=isDark;
        ui->btnChangeStyle->setStyleSheet("border-image:url(:/mainform/res/ChangeStyle_white.png)");
        ui->btnMenu->setStyleSheet("border-image:url(:/mainform/res/Menu_white.png)");
        repaint();
    }
    qssFile->open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile->readAll());
    qssFile->close();
    setStyleSheet(styleSheet);
    dark=isDark;

    this->setAttribute(Qt::WA_TranslucentBackground);
    delete qssFile;


}

void mainform::refreshStyleSheet()
{
    QSettings settings("Pinsoft","SecondDownloader");
    bool isDark=0;
    //QString rootReg="HKEY_LOCAL_MACHINE/SOFTWARE/Pinsoft/";
    // QMessageBox::information(this,QString::asprintf(rooReg.toLocal8Bit(),"%sSecondDownloader/Style/isDark"),QString::asprintf(rooReg.toLocal8Bit()));
    isDark=settings.value("Style/isDark",0).toBool();
    qDebug()<<isDark;
    QFile *qssFile=new QFile(this);
    if(isDark){
        qssFile->setFileName(":/mainform/qss/dark_mainform.qss");
        dark=isDark;
        ui->btnChangeStyle->setStyleSheet("border-image:url(:/mainform/res/ChangeStyle_dark.png)");
        ui->btnMenu->setStyleSheet("border-image:url(:/mainform/res/Menu_dark.png)");
        repaint();
    }else{
        qssFile->setFileName(":/mainform/qss/white_mainform.qss");
        dark=isDark;
        ui->btnChangeStyle->setStyleSheet("border-image:url(:/mainform/res/ChangeStyle_white.png)");
        ui->btnMenu->setStyleSheet("border-image:url(:/mainform/res/Menu_white.png)");
        repaint();
    }
    qssFile->open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile->readAll());
    qssFile->close();
    setStyleSheet(styleSheet);
    dark=isDark;


    delete qssFile;
}

void mainform::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);


    QColor color;
    if(dark)
        color.setRgb(36,36,36);
    else
        color.setRgb(249,249,249);
    QPen pen;
    pen.setWidth(0);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(color);
    QRect rect = this->rect();
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect,20,20);
    painter.end();
     QPainter siderBarPainter(this);
    //画出整个窗口

    QColor siderBarColor;
    if(dark)
        siderBarColor.setRgb(28,28,28);
    else
        siderBarColor.setRgb(243,243,243);
    siderBarPainter.setBrush(siderBarColor);
    siderBarPainter.setPen(Qt::transparent);
    siderBarPainter.drawRoundedRect(siderBarRect,20,20);
}

void mainform::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPos = event->globalPos() - pos();
    }
}

void mainform::mouseMoveEvent(QMouseEvent *event)
{

    if (m_moving && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }

}

void mainform::mouseReleaseEvent(QMouseEvent *event)
{
    m_moving=false;
}

void mainform::on_btnMin_clicked()
{
    showMinimized();
}


void mainform::on_btnChangeStyle_clicked()
{
    QSettings settings("Pinsoft","SecondDownloader");
    settings.setValue("Style/isDark",!dark);
    dark=!dark;
    QFile *qssFile=new QFile(this);
    if(dark)
    {
        // QIcon ico("border-image:url(’:/mainform/res/ChangeStyle_dark.png");
        // ui->btnChangeStyle->setIcon(ico);
        repaint();
        qssFile->setFileName(":/mainform/qss/dark_mainform.qss");
        ui->btnMenu->setStyleSheet("border-image:url(:/mainform/res/Menu_dark.png)");
        ui->btnChangeStyle->setStyleSheet("border-image:url(:/mainform/res/ChangeStyle_dark.png)");
    }else{
         // QIcon ico("border-image:url(’:/mainform/res/ChangeStyle_dark.png");
         // ui->btnChangeStyle->setIcon(ico);
         repaint();
         qssFile->setFileName(":/mainform/qss/white_mainform.qss");
         ui->btnMenu->setStyleSheet("border-image:url(:/mainform/res/Menu_white.png)");
         ui->btnChangeStyle->setStyleSheet("border-image:url(:/mainform/res/ChangeStyle_white.png)");
    }
    qssFile->open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile->readAll());
    qssFile->close();
    delete qssFile;
    setStyleSheet(styleSheet);
    mainPage->setDark(dark);
    dwncontent->setDark(dark);
    set->setDark(dark);
    donate->setDark(dark);
        // ui->btnChangeStyle->setStyleSheet("border-image:url(’:/mainform/res/ChangeStyle_white.png‘)");
}


void mainform::on_btnMainPage_clicked(bool checked)
{
    if(checked){
        ui->stackedWidget->setCurrentIndex(0);
        ui->btnDownloadContent->setChecked(0);
        ui->btnDonate->setChecked(0);
        ui->btnSettings->setChecked(0);
        ui->btnMainPage->setStyleSheet("border-image: url(:/mainform/res/"
                                       "Main-Page_selected_gradient.png);");
        ui->btnDownloadContent->setStyleSheet("border-image: url(:/mainform/res/"
                                              "Download-Content.png)");
        ui->btnDonate->setStyleSheet("border-image: url(:/mainform/res/"
                                              "Donate.png)");
        ui->btnSettings->setStyleSheet(" border-image: url(:/mainform/res/"
                                       "Settings.png)");
    }

}

void mainform::on_btnDownloadContent_clicked(bool checked)
{

    if(checked){
        ui->stackedWidget->setCurrentIndex(1);
        ui->btnMainPage->setChecked(0);
        ui->btnDonate->setChecked(0);
        ui->btnSettings->setChecked(0);
        ui->btnMainPage->setStyleSheet("border-image: url(:/mainform/res/"
                                       "Main-Page.png);");
        ui->btnDownloadContent->setStyleSheet("border-image: url(:/mainform/res/"
                                              "Download-Content_selected_gradient.png)");
        ui->btnDonate->setStyleSheet("border-image: url(:/mainform/res/"
                                     "Donate.png)");
        ui->btnSettings->setStyleSheet(" border-image: url(:/mainform/res/"
                                       "Settings.png)");
    }

}


void mainform::on_btnDonate_clicked(bool checked)
{

    if(checked){
        ui->stackedWidget->setCurrentIndex(2);
        ui->btnMainPage->setChecked(0);
        ui->btnDownloadContent->setChecked(0);
        ui->btnSettings->setChecked(0);
        ui->btnMainPage->setStyleSheet("border-image: url(:/mainform/res/"
                                       "Main-Page.png);");
        ui->btnDownloadContent->setStyleSheet("border-image: url(:/mainform/res/"
                                              "Download-Content.png)");
        ui->btnDonate->setStyleSheet("border-image: url(:/mainform/res/"
                                     "Donate_selected_gradient.png)");
        ui->btnSettings->setStyleSheet(" border-image: url(:/mainform/res/"
                                       "Settings.png)");
    }

}


void mainform::on_btnSettings_clicked(bool checked)
{

    if(checked){
        ui->stackedWidget->setCurrentIndex(3);
        ui->btnMainPage->setChecked(0);
        ui->btnDownloadContent->setChecked(0);
        ui->btnDonate->setChecked(0);
        ui->btnMainPage->setStyleSheet("border-image: url(:/mainform/res/"
                                       "Main-Page.png);");
        ui->btnDownloadContent->setStyleSheet("border-image: url(:/mainform/res/"
                                              "Download-Content.png)");
        ui->btnDonate->setStyleSheet("border-image: url(:/mainform/res/"
                                     "Donate.png)");
        ui->btnSettings->setStyleSheet(" border-image: url(:/mainform/res/"
                                       "Settings_selected_gradient.png)");
    }

}


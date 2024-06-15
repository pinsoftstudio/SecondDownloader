#include "header/mainform.h"
#include "ui_mainform.h"
#include <header/windowsizeadapter.h>
#include <QMessageBox>
#include <header/stackedwidgetadapter.h>
#include <QSettings>
#include <QDebug>
#include <QFile>
mainform::mainform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainform)
{
    ui->setupUi(this);
    adaptWindowAndControls();
    addWidgetTostackedWidget();
    adaptStackedWidgetAndSubControls();
    configWindowStyle();


}

mainform::~mainform()
{
    delete ui;
}

void mainform::adaptWindowAndControls()
{
     WindowSizeAdapter   adapter;
    adapter.setWindow(this);
    adapter.addWidget(this->ui->stackedWidget);
    adapter.addWidget(this->ui->btnClose);
    adapter.addWidget(this->ui->btnMin);
    adapter.addWidget(this->ui->btnSettings);
    adapter.addWidget(this->ui->btnChangeStyle);
    adapter.addWidget(this->ui->btnMainPage);
    adapter.addWidget(this->ui->btnDownloadContent);
    adapter.addWidget(this->ui->btnDonate);
    adapter.addWidget(this->ui->btnMenu);
    adapter.adaptAll();
}

void mainform::addWidgetTostackedWidget()
{   mainPage=new frmMainPage(this);
    dwncontent=new frmDownloadContent(this);
    set=new frmSettings(this);
    donate=new frmDonate(this);
    ui->stackedWidget->insertWidget(0,mainPage);
    ui->stackedWidget->insertWidget(1,dwncontent);
    ui->stackedWidget->insertWidget(2,set);
    ui->stackedWidget->insertWidget(3,donate);
    ui->stackedWidget->setCurrentIndex(0);

}

void mainform::adaptStackedWidgetAndSubControls()
{
    StackedWidgetAdapter *swadpt=new StackedWidgetAdapter(ui->stackedWidget);
    swadpt->setStackedWidget(ui->stackedWidget);
    swadpt->adapt();
}

void mainform::configWindowStyle()
{
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::FramelessWindowHint);
    QSettings settings("Pinsoft","SecondDownloader");
    bool isDark=0;
    QString rootReg="HKEY_LOCAL_MACHINE/SOFTWARE/Pinsoft/";
    // QMessageBox::information(this,QString::asprintf(rooReg.toLocal8Bit(),"%sSecondDownloader/Style/isDark"),QString::asprintf(rooReg.toLocal8Bit()));
    settings.setValue("Style/isDark",1);
    isDark=settings.value("Style/isDark",0).toBool();
    qDebug()<<isDark;
    QFile *qssFile=new QFile(this);
    if(isDark)
        qssFile->setFileName(":/mainform/qss/dark_mainform.qss");
    else
        qssFile->setFileName(":/mainform/qss/white_mainform.qss");
    qssFile->open(QIODevice::ReadOnly);
    QString styleSheet=QString::fromLatin1(qssFile->readAll());
    setStyleSheet(styleSheet);
    dark=isDark;
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明


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
    // 设置抗锯齿，不然边框会有明显锯齿
    painter.setBrush(color);
    // 设置窗体颜色
    QRect rect = this->rect();
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect,20,20);
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


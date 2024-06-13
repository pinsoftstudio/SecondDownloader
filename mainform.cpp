#include "mainform.h"
#include "ui_mainform.h"
#include <windowsizeadapter.h>
#include <QMessageBox>

mainform::mainform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainform)
{
    ui->setupUi(this);
    adaptWindowAndControls();
    addWidgetTostackedWidget();



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
    adapter.addWidget(this->ui->btnsettings);
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

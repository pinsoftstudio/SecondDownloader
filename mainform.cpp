#include "mainform.h"
#include "ui_mainform.h"
#include <windowsizeadapter.h>
#include <QMessageBox>
mainform::mainform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainform)
{
    ui->setupUi(this);
    WindowSizeAdapter   adapter;
    int a=this->geometry().x();
    QMessageBox::information(this,QString::number(a),QString::number(a));
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

mainform::~mainform()
{
    delete ui;
}

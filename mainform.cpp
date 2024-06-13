#include "mainform.h"
#include "ui_mainform.h"
#include <windowsizeadapter.h>
#include <QMessageBox>
mainform::mainform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainform)
{
    ui->setupUi(this);
    WindowSizeAdapter   Adapter;
    int a=this->geometry().x();
    QMessageBox::information(this,QString::number(a),QString::number(a));
    Adapter.setWindow(this);
    Adapter.adaptAll();
}

mainform::~mainform()
{
    delete ui;
}

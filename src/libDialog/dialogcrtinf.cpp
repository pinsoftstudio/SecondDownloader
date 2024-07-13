#include "dialogcrtinf.h"
#include "ui_dialogcrtinf.h"
#include "Style.h"

DialogCrtInf::DialogCrtInf(QWidget *parent)
    :  RadiusFrameLessDialog(parent)
    , ui(new Ui::DialogCrtInf)
{
     ui->setupUi(this);
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->btnYes->setProperty("highlight","true");

}

DialogCrtInf::~DialogCrtInf()
{
    delete ui;
}

void DialogCrtInf::setTitle(QString &title)
{
    strTitle=title;
    setWindowTitle(strTitle);
    ui->labTitle->setText(strTitle);

}

void DialogCrtInf::setText(QString &text)
{
    strText=text;
     ui->label_2->setText(strText);
}




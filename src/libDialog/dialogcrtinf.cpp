#include "dialogcrtinf.h"
#include "ui_dialogcrtinf.h"
#include "Style.h"

DialogCrtInf::DialogCrtInf(QWidget *parent)
    :  RadiusFrameLessDialog(parent)
    , ui(new Ui::DialogCrtInf)
{
     ui->setupUi(this);
    ui->btnYes->setProperty("highlight","true");
    addToStyleControl(this);
    setThisStyle();


    Dark=getIsDark();
    setDark(Dark);


    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

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

// void DialogCrtInf::paintEvent(QPaintEvent *event)
// {


//     QPainter painter(this);
//     QColor color;

//     if(Dark)
//         color.setRgb(36,36,36);
//     else
//         color.setRgb(249,249,249);
//     QPen pen;
//     pen.setWidth(0);
//     painter.setRenderHint(QPainter::Antialiasing);
//     painter.setBrush(color);
//     QRect rect = this->rect();
//     painter.setPen(Qt::transparent);
//     painter.drawRoundedRect(rect,20,20);

// }



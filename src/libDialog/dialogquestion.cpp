#include "dialogquestion.h"
#include "ui_dialogquestion.h"
#include "Style.h"

DialogQuestion::DialogQuestion(QWidget *parent)
    :  RadiusFrameLessDialog(parent)
    , ui(new Ui::DialogQuestion)
{
     ui->setupUi(this);
    ui->btnYes->setProperty("highlight","true");
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

}

DialogQuestion::~DialogQuestion()
{
    delete ui;
}

void DialogQuestion::setTitle(QString &title)
{
    strTitle=title;
    setWindowTitle(strTitle);
    ui->labTitle->setText(strTitle);

}

void DialogQuestion::setText(QString &text)
{
    strText=text;
     ui->label_2->setText(strText);
}


// void DialogQuestion::paintEvent(QPaintEvent *event)
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



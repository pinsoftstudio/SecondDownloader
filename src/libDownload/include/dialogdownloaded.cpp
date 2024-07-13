#include "dialogdownloaded.h"
#include "ui_dialogdownloaded.h"
#include "QPainter"
#include <Style.h>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
DialogDownloaded::DialogDownloaded(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogDownloaded)
{
    ui->setupUi(this);
    Qt::WindowFlags flags;
    setWindowFlags(flags|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute(Qt::WA_DeleteOnClose);
}

DialogDownloaded::~DialogDownloaded()
{

    delete ui;
}

void DialogDownloaded::setSavedLocation(QString location)
{
    fileLocation=location;
    QFileInfo fi(location);
    folderLocation=fi.absolutePath();
    ui->labmsg->setText(tr("下载完毕！文件 %1 已经保存至 %2 ").arg(fi.fileName()).arg(folderLocation));
}

void DialogDownloaded::paintEvent(QPaintEvent *event)
{
    Qt::WindowFlags flags;

    QPainter painter(this);
    QColor color;
    if(isDark())
        color.setRgb(43,43,43);
    else
        color.setRgb(255,255,255);
    QPen pen;
    pen.setWidth(1);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(QColor(151,151,151));
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(color);
    QRect rect = this->rect();
    painter.setPen(pen);
    painter.drawRoundedRect(rect,10,10);
    painter.end();
    QPainter shadePainter(this);
    shadePainter.setPen(Qt::transparent);
    if(isDark())
        color.setRgb(32,32,32);
    else
        color.setRgb(243,243,243);
    shadePainter.setBrush(color);

    shadePainter.drawRoundedRect(QRect(1,140,geometry().width()-2,geometry().height()-141),10,10);
    Q_UNUSED(event);
}

void DialogDownloaded::on_btnOpenFolder_clicked()
{
    QDesktopServices::openUrl(QUrl(QDir::fromNativeSeparators(folderLocation)));
    close();
}


void DialogDownloaded::on_btnOpen_clicked()
{
    QDesktopServices::openUrl(QUrl(QDir::fromNativeSeparators(fileLocation)));
    close();
}


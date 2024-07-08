#ifndef RADIUSFRAMELESSDIALOG_H
#define RADIUSFRAMELESSDIALOG_H

#endif // RADIUSFRAMELESSDIALOG_H
#include <QDialog>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
class RadiusFrameLessDialog:public QDialog
{
public:
    explicit RadiusFrameLessDialog(QWidget *parent = nullptr);
    ~RadiusFrameLessDialog();
    void setDark(bool dark);

private:
    bool Dark=1;
protected:
    void paintEvent(QPaintEvent *event);
};

inline RadiusFrameLessDialog::RadiusFrameLessDialog(QWidget *parent)
{
    if(parent!=nullptr) setParent(this);

}

inline RadiusFrameLessDialog::~RadiusFrameLessDialog()
{

}

inline void RadiusFrameLessDialog::setDark(bool dark)
{
    Dark=dark;
}

inline void RadiusFrameLessDialog::paintEvent(QPaintEvent *event)
{
    Qt::WindowFlags flags;

    QPainter painter(this);
    QColor color;
    if(Dark)
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
    if(Dark)
        color.setRgb(32,32,32);
    else
        color.setRgb(243,243,243);
    shadePainter.setBrush(color);

    shadePainter.drawRoundedRect(QRect(1,140,geometry().width()-2,geometry().height()-141),10,10);
}


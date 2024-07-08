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

}


#ifndef DIALOGCRTINF_H
#define DIALOGCRTINF_H

#include <QDialog>
#include <QPainter>
#include "RadiusFramelessDialog.h"
#include <QString>
#include "libDialog_global.h"
namespace Ui {
class DialogCrtInf;
}

class LIBDIALOG_EXPORT DialogCrtInf : public RadiusFrameLessDialog
{
    Q_OBJECT

public:
    explicit DialogCrtInf(QWidget *parent = nullptr);
    ~DialogCrtInf();
    QString strTitle;

    QString strText;

    void setTitle(QString &title);
    void setText(QString &text);

private:
    Ui::DialogCrtInf *ui;

protected:
    // void paintEvent(QPaintEvent *event);

};

#endif // DIALOGCRTINF_H

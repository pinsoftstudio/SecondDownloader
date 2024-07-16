#ifndef DIALOGQUESTION_H
#define DIALOGQUESTION_H

#include <QDialog>
#include <QPainter>
#include "RadiusFramelessDialog.h"
#include <QString>
#include "libDialog_global.h"
namespace Ui {
class DialogQuestion;
}

class LIBDIALOG_EXPORT DialogQuestion : public RadiusFrameLessDialog
{
    Q_OBJECT

public:
    explicit DialogQuestion(QWidget *parent = nullptr);
    ~DialogQuestion();
    QString strTitle;

    QString strText;

    void setTitle(QString &title);
    void setText(QString &text);


private:
    Ui::DialogQuestion *ui;

protected:
    // void paintEvent(QPaintEvent *event);

};

#endif // DIALOGQUESTION_H

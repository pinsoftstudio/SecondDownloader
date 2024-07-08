#ifndef DIALOGQUESTION_H
#define DIALOGQUESTION_H

#include <QDialog>
#include <QPainter>
#include <header/RadiusFramelessDialog.h>
#include <QString>
namespace Ui {
class DialogQuestion;
}

class DialogQuestion : public RadiusFrameLessDialog
{
    Q_OBJECT

public:
    explicit DialogQuestion(QWidget *parent = nullptr);
    ~DialogQuestion();
    QString strTitle;

    QString strText;
    bool Dark=0;
    void setTitle(QString &title);
    void setText(QString &text);

private:
    Ui::DialogQuestion *ui;

protected:
    // void paintEvent(QPaintEvent *event);

};

#endif // DIALOGQUESTION_H

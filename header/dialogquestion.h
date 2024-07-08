#ifndef DIALOGQUESTION_H
#define DIALOGQUESTION_H

#include <QDialog>
#include <QPainter>
#include <header/RadiusFramelessDialog.h>
namespace Ui {
class DialogQuestion;
}

class DialogQuestion : public RadiusFrameLessDialog
{
    Q_OBJECT

public:
    explicit DialogQuestion(QWidget *parent = nullptr);
    ~DialogQuestion();
    bool Dark=0;
private:
    Ui::DialogQuestion *ui;

protected:
    // void paintEvent(QPaintEvent *event);

};

#endif // DIALOGQUESTION_H

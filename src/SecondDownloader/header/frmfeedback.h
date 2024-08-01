#ifndef FRMFEEDBACK_H
#define FRMFEEDBACK_H

#include <QWidget>
#include <QWebEngineView>
namespace Ui {
class frmFeedback;
}

class frmFeedback : public QWidget
{
    Q_OBJECT

public:
    explicit frmFeedback(QWidget *parent = nullptr);
    ~frmFeedback();

private:
    Ui::frmFeedback *ui;
    ;
};

#endif // FRMFEEDBACK_H

#ifndef FRMMAINPAGE_H
#define FRMMAINPAGE_H

#include <QWidget>


namespace Ui {
class frmMainPage;
}

class frmMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit frmMainPage(QWidget *parent = nullptr);
    ~frmMainPage();

private:
    Ui::frmMainPage *ui;
};

#endif // FRMMAINPAGE_H

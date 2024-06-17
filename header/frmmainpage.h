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
    void setDark(bool isDark);
private:
    Ui::frmMainPage *ui;
    bool Dark=false;
    qint64 getInstalledDays();
};

#endif // FRMMAINPAGE_H

#ifndef FRMDONATE_H
#define FRMDONATE_H

#include <QWidget>


namespace Ui {
class frmDonate;
}

class frmDonate : public QWidget
{
    Q_OBJECT

public:
    explicit frmDonate(QWidget *parent = nullptr);
    ~frmDonate();
    void setDark(bool isDark);
private:
    Ui::frmDonate *ui;
    bool Dark=false;
};

#endif // FRMDONATE_H

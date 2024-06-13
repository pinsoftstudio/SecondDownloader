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

private:
    Ui::frmDonate *ui;
};

#endif // FRMDONATE_H

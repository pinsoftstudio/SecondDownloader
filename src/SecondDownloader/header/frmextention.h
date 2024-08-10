#ifndef FRMEXTENTION_H
#define FRMEXTENTION_H

#include <QWidget>

namespace Ui {
class frmExtention;
}

class frmExtention : public QWidget
{
    Q_OBJECT

public:
    explicit frmExtention(QWidget *parent = nullptr);
    ~frmExtention();

private slots:
    void on_btnStore_clicked();

    void on_btnCrx_clicked();

private:
    Ui::frmExtention *ui;
};

#endif // FRMEXTENTION_H

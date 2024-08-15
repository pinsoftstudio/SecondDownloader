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

    void on_btnchrome_clicked();

    void on_btn360_clicked();

    void on_btnMolizza_clicked();

    void on_btnmsedge_clicked();

private:
    Ui::frmExtention *ui;
};

#endif // FRMEXTENTION_H

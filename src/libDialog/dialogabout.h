#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>
#include "libDialog_global.h"
namespace Ui {
class DialogAbout;
}

 class LIBDIALOG_EXPORT DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = nullptr);
    ~DialogAbout();

private slots:
    void on_btnGithub_clicked();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H

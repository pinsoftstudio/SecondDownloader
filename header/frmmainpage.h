#ifndef FRMMAINPAGE_H
#define FRMMAINPAGE_H

#include <QWidget>
#include<QCloseEvent>

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
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_pushButton_clicked();
};

#endif // FRMMAINPAGE_H

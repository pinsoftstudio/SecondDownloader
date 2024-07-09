#ifndef FRMMAINPAGE_H
#define FRMMAINPAGE_H

#include <QWidget>
#include<QCloseEvent>
#include <newdownloadwindow.h>
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
    void iniControl();
    NewDownloadWindow *newDownload;
protected:
    void closeEvent(QCloseEvent *event) override;
signals:
    void  downloadThreadExist(DownloadWindow *downloadwindow);
private slots:
    void on_pushButton_clicked(bool checked);
    void on_toolNew_clicked();
    void  ondownloadThreadExist(DownloadWindow *downloadwindow);
};

#endif // FRMMAINPAGE_H

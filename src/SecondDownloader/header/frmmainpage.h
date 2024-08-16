#ifndef FRMMAINPAGE_H
#define FRMMAINPAGE_H

#include <QWidget>
#include<QCloseEvent>
#include <newdownloadwindow.h>
#include <dialogabout.h>
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
    inline void refresh(){
        iniControl();
    }
private:
    Ui::frmMainPage *ui;
    bool Dark=false;
    qint64 getInstalledDays();
    void iniControl();
    NewDownloadWindow *newDownload;


protected:
    void closeEvent(QCloseEvent *event) override;
signals:

    void requestPage(int i,int mode=0);
private slots:
    void on_pushButton_clicked(bool checked);
    void on_toolNew_clicked();
    void on_toolAll_clicked();
    void on_toolSuc_clicked();
    void on_toolDownloading_clicked();
    void on_toolFailed_clicked();
    void on_toolExtention_clicked();
    void on_toolDonate_clicked();
    void on_toolAbout_clicked();
};

#endif // FRMMAINPAGE_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frmmainpage.h"
#include <header/frmdownloadcontent.h>
#include "frmsettings.h"
#include "frmdonate.h"
#include "frmfeedback.h"
#include <downloadwindow.h>
 #include<QProcess>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( int mode,QWidget *parent = nullptr);
    ~MainWindow();

    void showWithMode(int mode);
private:
    frmMainPage *mainPage;
    frmDownloadContent *dwncontent;
    frmSettings *set;
    frmDonate *donate;
    frmFeedback *feedback;
    QTimer *tmGetClipUrl;
    QTimer *tmNeedLaunchGetUrl;
    QStringList LastUrlList;

    QProcess *pro;
    void addToLastUrlList();
private slots:
    void on_toolMenu_clicked();

    void on_toolMain_clicked();

    void on_toolDownload_clicked();

    void on_toolDonate_clicked();

    void on_toolSettings_clicked();

    void onRequestPageChange(int i, int mode);

    void onGetClipUrl();

    void on_toolFeedback_clicked();

    void on_toolUpdate_clicked();

private:
    Ui::MainWindow *ui;
    bool isDownloading();
    void setClassToolButtonStyle();
    void addWidgetTostackedWidget();
    bool needToIngore(QString );
};

#endif // MAINWINDOW_H

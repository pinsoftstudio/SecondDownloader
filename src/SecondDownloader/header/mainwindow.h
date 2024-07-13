#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frmmainpage.h"

#include "frmsettings.h"
#include "frmdonate.h"
#include <downloadwindow.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( int mode,QWidget *parent = nullptr);
    ~MainWindow();
    frmMainPage *mainPage;


    frmSettings *set;
    frmDonate *donate;

private slots:
    void on_toolMenu_clicked();

    void on_toolMain_clicked();

    void on_toolDownload_clicked();

    void on_toolDonate_clicked();

    void on_toolSettings_clicked();

    void  ondownloadThreadExist(DownloadWindow *downloadwindow)
    {
        emit downloadThreadExist(downloadwindow);
    }

signals:
    void  downloadThreadExist(DownloadWindow *downloadwindow);

private:
    Ui::MainWindow *ui;
    bool isDownloading();
    void setClassToolButtonStyle();
    void addWidgetTostackedWidget();
};

#endif // MAINWINDOW_H

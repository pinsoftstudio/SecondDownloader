#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frmmainpage.h"
#include <header/frmdownloadcontent.h>
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
    frmDownloadContent *dwncontent;
    frmSettings *set;
    frmDonate *donate;
    void showWithMode(int mode);
private slots:
    void on_toolMenu_clicked();

    void on_toolMain_clicked();

    void on_toolDownload_clicked();

    void on_toolDonate_clicked();

    void on_toolSettings_clicked();

    void onRequestPageChange(int i, int mode);


private:
    Ui::MainWindow *ui;
    bool isDownloading();
    void setClassToolButtonStyle();
    void addWidgetTostackedWidget();
};

#endif // MAINWINDOW_H

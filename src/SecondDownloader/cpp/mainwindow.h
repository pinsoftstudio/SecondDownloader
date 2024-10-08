#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header/frmmainpage.h"
#include "header/frmdownloadcontent.h"
#include "header/frmsettings.h"
#include "header/frmdonate.h"
#include "header/frmfeedback.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,int mode=0);
    ~MainWindow();
private:
    frmMainPage *mainPage;
    frmDownloadContent *dwncontent;
    frmSettings *set;
    frmDonate *donate;
    frmFeedback *feedback;
    QTimer *tmGetClipUrl;
public slots:
    void on_toolMenu_clicked();

    void on_toolMain_clicked();

    void on_toolDownload_clicked();

    void on_toolDonate_clicked();

    void on_toolSettings_clicked();

    void onTmGetClipUrl();







private slots:


private:
    Ui::MainWindow *ui;
    bool isDownloading();
    void setClassToolButtonStyle();
    void addWidgetTostackedWidget();
};

#endif // MAINWINDOW_H

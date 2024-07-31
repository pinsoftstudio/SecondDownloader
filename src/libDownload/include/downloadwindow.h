#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H
#include <QList>
#include <QMainWindow>
#include "libdownload.h"
#include <QTimer>
#include <QProgressBar>
#include "fileappender.h"
#include "QEvent"
#include "QSystemTrayIcon"
#include "QMenu"
#include "QSharedMemory"
#include "QDataStream"

namespace Ui {
class DownloadWindow;
}

class LIBDOWNLOAD_EXPORT DownloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWindow(QString url,QString saveFileName,qint64 totalBytes,QWidget *parent = nullptr);
    ~DownloadWindow();
    // struct sendShareDownloadData data;

private:
    // Qt UI 相关
    Ui::DownloadWindow *ui;
    QSystemTrayIcon *tray;
    QProgressBar *progressbar[8];
    QMenu *trayMenu;
    QAction actProgress;
    QSharedMemory *share;
    QSharedMemory *passKey;
    void iniSharedMemory();
    // 自定义类或其他类实例
    LibDownload *downloaders[8];
    fileAppender *appender;

    // 基本数据类型和容器
    QString URL;
    QString savedFilename;
    QString tempPath;
    QList<QString> tempFilePathNames;
    bool isMultipal = 1;
    bool needtoclose = 0;
    qint64 TotalBytes=0;
    qint64 commonToDownload;
    qint64 lastToDownload;
    qint64 downloaded[8];
    qint64 lastDownloaded = 0;
    qint64 nowDownloaded = 0;
    int finishedThreads = 0;

    // Qt 定时器
    QTimer *tmGetProgress;
    QTimer *tmsetMainProgress;
    QTimer *tmsendMemory;

    // 成员函数
    void makeAtray();
    void startDownload();
    QString randomPath();
    void getSuitableUnit(long double &bytes, QString &unit);
    void closeEvent(QCloseEvent *event) override;
    void cleanup();
    int percent=0;
    QString state;
    QString key;
    QString strspeed="0B/s";

private slots:
    void ondownloadFailed();
    void ondownloadFinished();
    void ontmGetProgress();
    void onsetMainProgress();
    void onGetAppendProgress(int now,int total);
    void onAppendFailed();
    void onAppendSucceed();
    void onMessageClicked();
    void onTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void onActionTriggered();
    void on_btncancel_clicked();
    void on_btnmin_clicked();
    void onsendMemory();
    void onOnlyOne();
};

#endif // DOWNLOADWINDOW_H

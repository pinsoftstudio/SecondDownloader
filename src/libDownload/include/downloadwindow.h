#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H
#include <QList>
#include <QWidget>
#include "libdownload.h"
#include <QTimer>
#include <QProgressBar>
namespace Ui {
class DownloadWindow;
}

class LIBDOWNLOAD_EXPORT DownloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWindow(QString url,QString saveFileName,qint64 totalBytes,QWidget *parent = nullptr);
    ~DownloadWindow();


private:
    Ui::DownloadWindow *ui;
    // LibDownload *downloader;
    QString URL;
    QString savedFilename;
    QString tempPath;
    qint64 TotalBytes;
    LibDownload *downloaders[8];
    void startDownload();
    QString randomPath();
    QList<QString> tempFilePathNames;
    bool isMultipal=1;
    qint64 commonToDownload;
    qint64 lastToDownload;
    QTimer *tmGetProgress;
    QTimer *tmsetMainProgress;
    QProgressBar *progressbar[8];
    qint64 downloaded[8];
    qint64 lastDownloaded=0;
    qint64 nowDownloaded=0;
    // double downloadedBytes;

signals:
    void  downloadThreadExist(DownloadWindow *download);
private slots:
    void  ondownloadThreadExist(DownloadWindow *download);
    void ondownloadFailed();
    void ondownloadFinished();
    void ontmGetProgress();
    void onsetMainProgress();

    // void on_btnDisplay_clicked(bool checked);
};

#endif // DOWNLOADWINDOW_H

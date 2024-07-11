#ifndef DOWNLOADMESSAGEWINDOW_H
#define DOWNLOADMESSAGEWINDOW_H

#include <QWidget>
#include "downloadwindow.h"
#include "libDownload_global.h"
#include "QIcon"
#include "QPixmap"
namespace Ui {
class LIBDOWNLOAD_EXPORT DownloadMessageWindow;
}

class LIBDOWNLOAD_EXPORT DownloadMessageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadMessageWindow(QString url,QWidget *lastWindow,QWidget *parent = nullptr);
    ~DownloadMessageWindow();

private:
    Ui::DownloadMessageWindow *ui;
    DownloadWindow *downloadwindow;
    QString URL;
    QString finalSize;
    QString savingLocation;
    QString savedFileName;
    qint64 size=0;
    void iniUi();
    QPixmap getFilePixmap(QString fileLocation);
    QWidget *LastWindow;
    QTimer tmGetprogress;
signals:
    void  downloadThreadExist(DownloadWindow *downloadwindow);
private slots:
    void  ondownloadThreadExist(DownloadWindow *downloadwindow);
    void onresultready(qint64 filesize);
    void on_btnStart_clicked();
    void ongeterror();
    void on_btnChoose_clicked();

};

#endif // DOWNLOADMESSAGEWINDOW_H



#ifndef FILEURLINFO_H
#define FILEURLINFO_H

#include <QObject>
#include "curl/curl.h"
#include "libDownload_global.h"

class LIBDOWNLOAD_EXPORT FileUrlInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileUrlInfo(QString url, QObject *parent = nullptr) : QObject(parent), URL(url) {}

signals:
    void resultReady(qint64 fileSize);
    void getERROR();

private:
    QString URL;
    CURL *curl;
    CURLcode res;

public slots:
    void getFileSize()
    {
        double contentLength = 0.0;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (!curl) {
            emit getERROR();
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, URL.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // 发送 HEAD 请求
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // 跟随重定向

        // 执行 HEAD 请求
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            emit getERROR();
            curl_easy_cleanup(curl);
            return;
        }

        // 获取文件大小
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &contentLength);
        if (res != CURLE_OK) {
            emit getERROR();
        } else {
            emit resultReady(static_cast<qint64>(contentLength));
        }

        // 清理 curl 句柄
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
};

#endif // FILEURLINFO_H



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
    explicit DownloadMessageWindow(QString url, QWidget *lastWindow,bool passedNull, QWidget *parent = nullptr);
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
    bool passedNULL;
    QPixmap getFilePixmap(QString fileLocation);
    QWidget *LastWindow;
    QTimer tmGetprogress;

private slots:
    void onsizeready(qint64 filesize);
    void onurlready(QString finalUrl);
    // void onfileNameReady(QString fileName);
    void on_btnStart_clicked();
    void ongeterror();
    void on_btnChoose_clicked();

};

#endif // DOWNLOADMESSAGEWINDOW_H



#ifndef FILEURLINFO_H
#define FILEURLINFO_H
#include "QThread"
#include <QObject>
#include "curl/curl.h"
#include "libDownload_global.h"
#include "string"
#include "QDebug"

static int xferinfo_callback(void *clientp,
                             curl_off_t dltotal, curl_off_t dlnow,
                             curl_off_t ultotal, curl_off_t ulnow) ;

class LIBDOWNLOAD_EXPORT FileUrlInfo : public QThread
{
    Q_OBJECT
public:
    explicit FileUrlInfo(QString url) :  URL(url) {}
    void  fakeDownloadFinished(qint64 fileSize)
    {
        emit sizeReady(fileSize);
        this->terminate();
        wait();

    }
signals:
    void UrlReady(QString finalUrl);
    void getERROR();
    void sizeReady(qint64 fileSize);
    void nameReady(QString finalName);
private:
    QString URL;
    CURL *curl;
    CURLcode res;
protected:
    void run()  Q_DECL_OVERRIDE
    {
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (!curl) {
            emit getERROR();
        }

        char* url=NULL;
        std::string *name;
        QString range = "bytes=0-"; // 指定下载的文件范围
        // struct curl_slist *headers = nullptr;

        // headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,en-GB;q=0.6");
        // headers = curl_slist_append(headers, "Sec-CH-UA: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"102\", \"Microsoft Edge\";v=\"102\"");
        // headers = curl_slist_append(headers, "Sec-CH-UA-Mobile: ?0");
        // headers = curl_slist_append(headers, "Sec-CH-UA-Platform: \"Windows\"");
        // headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
        // headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
        // headers = curl_slist_append(headers, "Sec-Fetch-Site: cross-site");
        // headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.30");
        // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
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
        res=curl_easy_getinfo(curl,CURLINFO_EFFECTIVE_URL,&url);
        qDebug()<<url;
        emit UrlReady(url);
        res=curl_easy_perform(curl);
        // res=curl_easy_getinfo(curl,CURLINFO_EFFECTIVE_URL,&url);
        CURLcode res = curl_easy_perform(curl);
        if (res = CURLE_OK) {
            qDebug()<<url;
            emit UrlReady(url);
        }
        URL=url;

        struct curl_slist *headers1 = nullptr;
        headers1 = curl_slist_append(headers1, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,en-GB;q=0.6");
        headers1 = curl_slist_append(headers1, "Sec-CH-UA: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"102\", \"Microsoft Edge\";v=\"102\"");
        headers1 = curl_slist_append(headers1, "Sec-CH-UA-Mobile: ?0");
        headers1 = curl_slist_append(headers1, "Sec-CH-UA-Platform: \"Windows\"");
        headers1 = curl_slist_append(headers1, "Sec-Fetch-Dest: empty");
        headers1 = curl_slist_append(headers1, "Sec-Fetch-Mode: cors");
        headers1 = curl_slist_append(headers1, "Sec-Fetch-Site: cross-site");
        headers1 = curl_slist_append(headers1, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.30");
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 5);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 1000L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers1);
        curl_easy_setopt(curl, CURLOPT_URL, URL.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0L); // 发送 HEAD 请求
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // 跟随重定向
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo_callback);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L); // 确保启用进度报告
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
        curl_easy_perform(curl);
        // curl_slist_free_all(headers);
        curl_slist_free_all(headers1);
        curl_easy_cleanup(curl);
        // double contentLength = 0.0;
        // char* url=NULL;
        // curl_global_init(CURL_GLOBAL_ALL);
        // curl = curl_easy_init();
        // if (!curl) {
        //     emit getERROR();
        //     return;
        // }

        // struct curl_slist *headers = nullptr;

        // headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,en-GB;q=0.6");
        // headers = curl_slist_append(headers, "Sec-CH-UA: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"102\", \"Microsoft Edge\";v=\"102\"");
        // headers = curl_slist_append(headers, "Sec-CH-UA-Mobile: ?0");
        // headers = curl_slist_append(headers, "Sec-CH-UA-Platform: \"Windows\"");
        // headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
        // headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
        // headers = curl_slist_append(headers, "Sec-Fetch-Site: cross-site");
        // headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.30");
        // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // curl_easy_setopt(curl, CURLOPT_URL, URL.toStdString().c_str());
        // curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // 发送 HEAD 请求
        // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // 跟随重定向

        // // 执行 HEAD 请求
        // res = curl_easy_perform(curl);
        // if (res != CURLE_OK) {
        //     emit getERROR();
        //     curl_easy_cleanup(curl);
        //     return;
        // }

    }
};

static int xferinfo_callback(void *clientp,
                             curl_off_t dltotal, curl_off_t dlnow,
                             curl_off_t ultotal, curl_off_t ulnow) {
    Q_UNUSED(ultotal);
    Q_UNUSED(ulnow);

    // LibDownload *downloader=static_cast<LibDownload*>(clientp);
    // if (dltotal > 0) {
    //     double percent = (double)dlnow / dltotal * 100.0;
    //     downloader->setCtotal(dltotal);
    //     downloader->setCnow(dlnow);
    //         // downloader->setUnknown(0);
    //     qDebug() << "Downloaded" << dlnow << "of" << dltotal << "bytes (" << percent << "%)";
    // } else {

    //     downloader->setCnow(dlnow);
    //     // downloader->setUnknown(1);
    //     qDebug() << "Downloaded" << dlnow << "bytes (total size unknown)";
    // }
    if(dltotal>0){
        FileUrlInfo *fileUrlinfo=static_cast<FileUrlInfo*>(clientp);
        double dtotal=(double)dltotal;

        fileUrlinfo->fakeDownloadFinished(static_cast<qint64>(dtotal));


    }
    return 0; // 成功
}

#endif // FILEURLINFO_H



#ifndef DOWNLOADMESSAGEWINDOW_COPY_H
#define DOWNLOADMESSAGEWINDOW_COPY_H

#include <QWidget>
#include "downloadwindow.h"
#include "libDownload_global.h"
#include "QIcon"
#include "QPixmap"
#include <cstdio>
#include <string>
#include <iostream>
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
    void onresultready(qint64 filesize,QString finalUrl);
    void on_btnStart_clicked();
    void ongeterror();
    void on_btnChoose_clicked();

};

#endif // DOWNLOADMESSAGEWINDOW_COPY_H



#ifndef FILEURLINFO_H
#define FILEURLINFO_H

#include <QObject>
#include "curl/curl.h"
#include "libDownload_global.h"
static QString size;
static size_t HeaderCallback(void *ptr, size_t size, size_t nmemb, std::string *userp) {
    size_t realsize = size * nmemb;
    const char *header = static_cast<const char *>(ptr);

    // 查找Content-Length
    if (strncmp(header, "Content-Length:", 14) == 0) {
        // 跳过"Content-Length: "并获取值
        size_t len = strlen(header) - 14;
        if (len > 0) {
            userp->append(header + 14, len);
            userp->append("\n"); // 假设你需要在字符串末尾添加换行符
        }
    }

    qDebug()<<userp;



    return realsize;
}
class LIBDOWNLOAD_EXPORT FileUrlInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileUrlInfo(QString url, QObject *parent = nullptr) : QObject(parent), URL(url) {}

signals:
    void resultReady(qint64 fileSize,QString finalUrl);
    void getERROR();

private:
    QString URL;
    CURL *curl;
    CURLcode res;

public slots:
    void getFileSize()
    {
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

        // // 获取文件大小

        // res=curl_easy_getinfo(curl,CURLINFO_EFFECTIVE_URL,&url);
        // qDebug()<<url;
        // res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &contentLength);
        // if (res != CURLE_OK) {
        //     emit getERROR();
        // } else {
        //     emit resultReady(static_cast<qint64>(contentLength),QString::fromLocal8Bit(url));
        // }

        // // 清理 curl 句柄
        // curl_easy_cleanup(curl);
        // curl_global_cleanup();


        CURL *curl;
        CURLcode res;

        curl_global_init(CURL_GLOBAL_ALL);

        curl = curl_easy_init();
        if (curl) {
            std::string contentLength;
            struct curl_slist *headers = nullptr;

            // 设置URL
            headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,en-GB;q=0.6");
            headers = curl_slist_append(headers, "Sec-CH-UA: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"102\", \"Microsoft Edge\";v=\"102\"");
            headers = curl_slist_append(headers, "Sec-CH-UA-Mobile: ?0");
            headers = curl_slist_append(headers, "Sec-CH-UA-Platform: \"Windows\"");
            headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
            headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
            headers = curl_slist_append(headers, "Sec-Fetch-Site: cross-site");
            headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.30");

            curl_easy_setopt(curl, CURLOPT_URL, URL.toStdString().c_str());

            // 设置请求方法为HEAD
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

            // 设置响应头回调函数
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &contentLength);

            // 执行请求
            res = curl_easy_perform(curl);

            // 检查错误
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                // 去除可能的尾随换行符
                if (!contentLength.empty() && contentLength.back() == '\n') {
                    contentLength.pop_back();
                }
                std::cout << "Content-Length: " << contentLength << std::endl;
            }

            // 清理
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();






    }
};

#endif // FILEURLINFO_H



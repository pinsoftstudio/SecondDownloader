#include "libdownload.h"
#include "QFile"
#include "cstdio"
#include "QString"
#include "QDebug"
static size_t write_to_file(void *ptr, size_t size, size_t nmemb, QFile *file) {
    size_t total_size = size * nmemb;
    if (file->write(static_cast<char*>(ptr), total_size) != total_size) {
        qDebug() << "Failed to write data to file";
        return 0;
    }
    return total_size;
}
static int xferinfo_callback(void *clientp,
                             curl_off_t dltotal, curl_off_t dlnow,
                             curl_off_t ultotal, curl_off_t ulnow) {
    Q_UNUSED(ultotal);
    Q_UNUSED(ulnow);
    LibDownload *downloader=static_cast<LibDownload*>(clientp);
    if (dltotal > 0) {
        double percent = (double)dlnow / dltotal * 100.0;
         downloader->setCtotal(dltotal);
        downloader->setCnow(dlnow);
         // downloader->setUnknown(0);
        // qDebug() << "Downloaded" << dlnow << "of" << dltotal << "bytes (" << percent << "%)";
    } else {

         downloader->setCnow(dlnow);
        // downloader->setUnknown(1);
        // qDebug() << "Downloaded" << dlnow << "bytes (total size unknown)";
    }

    return 0; // 成功
}
LibDownload::LibDownload(QString startBytes,QString endBytes,QString savingLocation,QString &downloadURL,QObject *parent = nullptr) : QThread(parent) {

    curl_global_init(CURL_GLOBAL_ALL);
    StartBytes=startBytes;
    EndBytes=endBytes;
    location=savingLocation;
    URL=downloadURL;
    qDebug()<<"CBegin";
}

LibDownload::~LibDownload()
{
    if (curl) {
        curl_easy_cleanup(curl);
    }

}

void LibDownload::getDownloadProgress(double &now, double &total)
{
    now=Cnow;
    total=Ctotal;
}

void LibDownload::setCnow(double now)
{
    Cnow=now;
}

void LibDownload::setCtotal(double total)
{
    Ctotal=total;
}

void LibDownload::setUnknown(bool unknown)
{
    unknownTotal=unknown;
}

void LibDownload::run()
{

    curl = curl_easy_init();
    if (!curl) {
        emit downloadFailed();

    }


    QString range = "bytes="+StartBytes+"-"+EndBytes; // 指定下载的文件范围

    QFile file(location);
    if (!file.open(QIODevice::WriteOnly)) {
         emit downloadFailed();
        curl_easy_cleanup(curl);

    }

    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, ("Range: " + range.toStdString()).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, URL.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 5);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 1000);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo_callback);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L); // 确保启用进度报告
   curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);


    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
         emit downloadFailed();
    } else {
        emit downloadFinished();
    }

    file.close();
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}

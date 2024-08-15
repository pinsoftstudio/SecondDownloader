#include "libdownload.h"
#include "QFile"
#include "cstdio"
#include "QString"
#include "QDebug"
#include "QRegularExpression"
#include "QByteArray"
static size_t header_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    fwrite(contents, size, nmemb, stdout);
    LibDownload *downloader=static_cast<LibDownload*>(userp);


    QRegularExpression exp("filename=[\"']?([^\"'\r\n]+)\1?[\r\n]?");
    QString headContent=QString::fromUtf8(static_cast<char*>(contents));
    qDebug()<<headContent;
    QRegularExpressionMatchIterator it=exp.globalMatch(headContent);
    while(it.hasNext()){
        QRegularExpressionMatch match=it.next();
        QString filename=match.captured(1);
        if(filename.contains('%')){
            QByteArray encodedString=filename.toUtf8();
            QByteArray decodedBytes=QByteArray::fromPercentEncoding(encodedString);
            filename= QString::fromUtf8(decodedBytes);

        }
        downloader->setFileName(filename);
    }

    exp.setPattern("200 OK");
    it=exp.globalMatch(headContent);
    if(it.hasNext()){
        downloader->emitOnlyOne();


    }


    return size * nmemb;
}
static size_t header_callback_forNoGetName(void *contents, size_t size, size_t nmemb, void *userp) {
    fwrite(contents, size, nmemb, stdout);
    LibDownload *downloader=static_cast<LibDownload*>(userp);


    QRegularExpression exp("200 OK");
    QString headContent=QString::fromUtf8(static_cast<char*>(contents));
    qDebug()<<headContent;
    QRegularExpressionMatchIterator it;
    it=exp.globalMatch(headContent);
    if(it.hasNext()){
        downloader->stopDownload();
        downloader->setNoEmitSuccess();

    }


    return size * nmemb;
}
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
LibDownload::LibDownload(QString startBytes, QString endBytes, QString savingLocation, QString &downloadURL, bool getFileName, QObject *parent , QMap<QString, QString> cookieMap) : QThread(parent) {

    curl_global_init(CURL_GLOBAL_ALL);
    StartBytes=startBytes;
    EndBytes=endBytes;
    location=savingLocation;
    URL=downloadURL;
    getName=getFileName;
    mapCookie=cookieMap;
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

void LibDownload::setFileName(QString fileName)
{
    truefileName=fileName;
}

void LibDownload::setUnknown(bool unknown)
{
    unknownTotal=unknown;
}

QString LibDownload::getTrueFileName()
{

    return truefileName;
}

void LibDownload::emitOnlyOne()
{
    emit onlyOne();
}

void LibDownload::setNoEmitSuccess()
{
    noEmitSuccess=1;
}

void LibDownload::stopDownload()
{
    curl_easy_pause(curl, CURLPAUSE_RECV);
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
    QMap<QString,QString>::const_iterator i=mapCookie.constBegin();
    std::string strCookie;
    while(i!=mapCookie.constEnd()){
        QString acookie=i.key()+"="+i.value()+";";
        strCookie+=acookie.toStdString();

        ++i;
    }
    headers = curl_slist_append(headers, ("Range: " + range.toStdString()).c_str());
    headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7,en-GB;q=0.6");
    headers = curl_slist_append(headers, "Sec-CH-UA: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"102\", \"Microsoft Edge\";v=\"102\"");
    headers = curl_slist_append(headers, "Sec-CH-UA-Mobile: ?0");
    headers = curl_slist_append(headers, "Sec-CH-UA-Platform: \"Windows\"");
    headers = curl_slist_append(headers, "Sec-Fetch-Dest: empty");
    headers = curl_slist_append(headers, "Sec-Fetch-Mode: cors");
    headers = curl_slist_append(headers, "Sec-Fetch-Site: cross-site");
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.30");

    curl_easy_setopt(curl, CURLOPT_URL, URL.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 5);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 1000L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo_callback);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L); // 确保启用进度报告
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
    curl_easy_setopt(curl,CURLOPT_HEADEROPT,1L);
    curl_easy_setopt(curl,CURLOPT_COOKIE,strCookie.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, this);
    if(getName){  
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    }else{
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback_forNoGetName);
    }



    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        if(!noEmitSuccess){
         emit downloadFailed();
        }
    } else {
        if(!noEmitSuccess){
        emit downloadFinished();
        }
    }

    file.close();
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

}

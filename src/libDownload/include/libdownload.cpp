#include "libdownload.h"
#include "QFile"
#include "cstdio"
static int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
    LibDownload *downloader = static_cast<LibDownload*>(clientp);
    downloader->setCnow(dlnow);
    downloader->setCtotal(dltotal);
    Q_UNUSED(ultotal);
    Q_UNUSED(ulnow);

    // qDebug() << "Downloaded:" << dlnow << "of" << dltotal;
    return 0;
}

size_t function(void *bufptr, size_t size, size_t nitems, FILE *userp){
    size_t written=fwrite(bufptr,size,nitems,userp);
    return written;
}

LibDownload::LibDownload(QString startBytes,QString endBytes,QObject *parent = nullptr) : QThread(parent) {

}

LibDownload::~LibDownload()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

void LibDownload::setCnow(double now)
{
    Cnow=now;
}

void LibDownload::setCtotal(double total)
{
    Ctotal=total;
}

void LibDownload::run()
{
    curl=curl_easy_init();
    if(!curl){
        emit downloadFailed();
        return;
    }else {
        QString fileName=downloadUrl.right(downloadUrl.length()-
                                             downloadUrl.lastIndexOf("/"));
        QString saveFilePath=location+fileName;

        file = fopen(saveFilePath.toLocal8Bit().constData(), "wb");
        if(file!=nullptr){

            curl_easy_setopt(curl,CURLOPT_URL,downloadUrl.toUtf8().constData());
            //指定下载URL
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,function);
            //指定下载写入的回调函数
            curl_easy_setopt(curl,CURLOPT_WRITEDATA,file);
            //指定下载的文件
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
            curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);

            if(QFile(saveFilePath).exists()){
                QFile(saveFilePath).moveToTrash();
            }
            res=curl_easy_perform(curl);
        }else {
            emit downloadFailed();
            return;
        }
        if(res == CURLE_OK){
            emit downloadFinished();
        }else{
            emit downloadFailed();
        }
        fclose(file);
        curl_easy_cleanup(curl);
        file=nullptr;

    }
}

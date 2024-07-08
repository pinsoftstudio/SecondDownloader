#ifndef LIBDOWNLOAD_H
#define LIBDOWNLOAD_H

#include "libDownload_global.h"
#include "curl.h"
#include "QThread"
// namespace Ui {
// class LibDownload;
// }
// LIBDOWNLOAD_EXPORT static void  curlStart();
// LIBDOWNLOAD_EXPORT static void  curlStart(){


// }

class LIBDOWNLOAD_EXPORT LibDownload:public QThread
{
    Q_OBJECT

public:
    explicit LibDownload(QString startBytes,QString endBytes,QObject *parent);
    ~LibDownload();
    void getDownloadProgress(double &now,double &total);
    void setCnow(double now);
    void setCtotal(double total);
private:
    QString downloadUrl;
    QString location;
    CURL *curl;
    FILE *file;
    CURLcode res;
    double Cnow=0;
    double Ctotal=0;
protected:
    void run() Q_DECL_OVERRIDE;
signals:
    void downloadFinished();
    void downloadFailed();
};



#endif // LIBDOWNLOAD_H

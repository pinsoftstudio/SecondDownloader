#ifndef LIBDOWNLOAD_H
#define LIBDOWNLOAD_H

#include "libDownload_global.h"
#include "curl/curl.h"
#include "QThread"
#include "cstdio"
#include "string"
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
    explicit LibDownload(QString startBytes,QString endBytes,QString savingLocation,QString &downloadURL,QObject *parent);
    ~LibDownload();
    void getDownloadProgress(double &now,double &total);
    void setCnow(double now);
    void setCtotal(double total);
    void setUnknown(bool unknown);
private:
    QString downloadUrl;
    // QString location;
    CURL *curl;

    CURLcode res;
    double Cnow=0;
    double Ctotal=0;
    bool unknownTotal=0;
    QString location;
   QString StartBytes;
    QString EndBytes;
    QString URL;
protected:
    void run() Q_DECL_OVERRIDE;
signals:
    void downloadFinished();
    void downloadFailed();
};



#endif // LIBDOWNLOAD_H

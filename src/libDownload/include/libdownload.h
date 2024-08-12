#ifndef LIBDOWNLOAD_H
#define LIBDOWNLOAD_H

#include "libDownload_global.h"
#include "curl/curl.h"
#include "QThread"
#include "cstdio"
#include "string"
#include "QMap"

class LIBDOWNLOAD_EXPORT LibDownload:public QThread
{
    Q_OBJECT

public:
    explicit LibDownload(QString startBytes,QString endBytes,QString savingLocation,QString &downloadURL,bool getFileName,QObject *parent=nullptr,QMap<QString,QString> cookieMap={});
    ~LibDownload();
    void getDownloadProgress(double &now,double &total);
    void setCnow(double now);
    void setCtotal(double total);
    void setFileName(QString fileName);
    void setUnknown(bool unknown);
    QString getTrueFileName();
    void emitOnlyOne();
    void setNoEmitSuccess();
    void stopDownload();

private:
    QString downloadUrl;
    // QString location;
    CURL *curl;
    bool getName=0;
    CURLcode res;
    double Cnow=0;
    double Ctotal=0;
    bool unknownTotal=0;
    bool noEmitSuccess=0;
    QString location;
    QString StartBytes;
    QString EndBytes;
    QString URL;
    QString truefileName="";
    QMap<QString,QString> mapCookie;

protected:
    void run() Q_DECL_OVERRIDE;
signals:
    void onlyOne();
    void downloadFinished();
    void downloadFailed();

};



#endif // LIBDOWNLOAD_H

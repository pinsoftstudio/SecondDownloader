#include "analyser.h"
#include "curl/curl.h"
Analyser::Analyser(QString FilePath) {
    file.setFileName(FilePath);
}
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    Analyser *an=static_cast<Analyser*>(userp);
    size_t realsize = size * nmemb;
    char* charResult=static_cast<char*>(contents);
    an->result+=QString::fromUtf8(charResult,realsize);
    return realsize;
}
void Analyser::run()
{
    if(!file.open(QIODevice::ReadOnly)){
        emit analyseFailed();
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(file.readAll());
    QByteArray array=hash.result();
    QString sha256=array.toHex();

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl=curl_easy_init();
    QString url="https://www.virustotal.com/api/v3/files/"+sha256;
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,this);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, "x-apikey: d151a59841528b29ed606e96c77644a67db33cf893b7bb0a556342043410fb76");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(curl);
    if(ret!=CURLE_OK){
        emit analyseFailed();
        return;
    }else{
        emit analyseFinished(result);
    }
}

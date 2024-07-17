#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QString>
// 从标准输入读取一条消息
std::string readMessage() {
    uint32_t len = 0;
    std::cin.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len == 0) {
        return "";
    }

    std::string message;
    message.resize(len);
    std::cin.read(&message[0], len);
    return message;
}

// 向标准输出写入一条消息
QString stdStringToQString(const std::string &str) {
    return QString::fromUtf8(str.c_str());
}

// 解析JSON并获取"url"的函数
QString getUrlFromJsonString(const QString &jsonStr) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    if (!doc.isObject()) {
        qDebug() << "JSON document is not an object";
        return QString();
    }

    QJsonObject obj = doc.object();
    if (!obj.contains("url")) {
        qDebug() << "\"url\" key not found in JSON object";
        return QString();
    }

    QString url = obj["url"].toString();
    return url;
}
void sendMessage(const std::string& message) {
    uint32_t len = message.size();
    std::cout.write(reinterpret_cast<const char*>(&len), sizeof(len));
    std::cout << message;
    std::cout.flush();
}

int main() {
    while (true) {
        std::string input = readMessage();
        if (input.empty()) {
            break;
        }

        // 在这里处理接收到的消息

        // 将std::string转换为QString
        QString qJsonStr = stdStringToQString(input);

        // 解析JSON并获取"url"
        QString url = getUrlFromJsonString(qJsonStr);

        system("SecondDownloader.exe "+url.toLocal8Bit());
        // 假设这里处理接收到的消息，然后向扩展发送响应
        std::string response = "Received URL: " + input;
        sendMessage(response);

    }
    return 0;
}

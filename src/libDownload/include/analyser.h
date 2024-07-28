#ifndef ANALYSER_H
#define ANALYSER_H

#include <QObject>
#include <QThread>
#include <QCryptographicHash>
#include <QFile>
#include <QByteArray>
class Analyser:public QThread
{
    Q_OBJECT
public:
    Analyser(QString FilePath);
    QString result;

private:
    QFile file;

protected:
    void run() Q_DECL_OVERRIDE;
signals:
    void analyseFinished(QString results);
    void analyseFailed();


};

#endif // ANALYSER_H

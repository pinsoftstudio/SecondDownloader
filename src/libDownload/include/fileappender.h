#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

#include <QObject>
#include <QThread>
#include <QList>

class fileAppender : public QThread
{
    Q_OBJECT
public:
    explicit fileAppender(QString savinglocation, QObject *parent = nullptr);
    void addToFileList(QString filePathName);

private:
    QList<QString> tempfileList;
    QString savingLocation;
    void run()  Q_DECL_OVERRIDE;
    void cleanup();
    bool multipal=1;
signals:
    void appendFailed();
    void appendSucceed();
    void appendProgress(int now,int total);



};

#endif // FILEAPPENDER_H
